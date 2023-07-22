/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/22 17:05:41 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/wait.h>

int	input(t_cmd *cmd, t_data *data, int in_fd)
{
	t_content	*content;
	t_list		*in;

	in = cmd->in;
	while (in != NULL)
	{
		content = ((t_content *)(in->content));
		if (check_file(data, content->word, R_OK) == 0)
			in_fd = open(content->word, O_RDONLY, 0644);
		else
			in_fd = -1;
		if (content->token == HEREDOC)
			unlink(content->word);
		in = in->next;
		if (in != NULL && in_fd != -1)
			close(in_fd);
	}
	if (cmd->prev != NULL && cmd->in == NULL)
		in_fd = cmd->prev->fd[0];
	if (in_fd == -1)
		return (-1);
	dup2(in_fd, STDIN_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	return (in_fd);
}

int	output(t_cmd *cmd, t_data *data)
{
	t_content	*content;
	t_list		*out;
	int			out_fd;

	out = cmd->out;
	out_fd = STDOUT_FILENO;
	while (out != NULL)
	{
		content = ((t_content *)(out->content));
		if (content->token == OUT)
			out_fd = open(content->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (content->token == APPEND)
			out_fd = open(content->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			out_fd = -1;
		if (check_file(data, content->word, W_OK) != 0)
			return (-1);
		out = out->next;
	}
	if (out_fd == -1)
		return (-1);
	dup2(out_fd, STDOUT_FILENO);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	return (out_fd);
}

int	pipeline(t_data *data, t_cmd *cmd, char **envp)
{
	pid_t	proc;
	int		in_fd;
	int		out_fd;
	int		status;

	in_fd = input(cmd, data, STDIN_FILENO);
	if (in_fd == -1)
		return (data->my_errno);
	out_fd = output(cmd, data);
	if (out_fd == -1)
		return (data->my_errno);
	if (pipe(cmd->fd) != 0)
		return (errno);
	proc = fork();
	if (proc == -1)
		return (errno);
	else if (proc == 0)
		child_exec(data, cmd, envp);
	close(cmd->fd[1]);
	signals_parent();
	if (dup2(cmd->fd[0], STDIN_FILENO) > 0 && cmd->out != NULL)
		write_output(STDIN_FILENO, STDOUT_FILENO);
	if (waitpid(proc, &status, WNOHANG) && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	last_cmd(t_data *data, t_cmd *cmd, char **envp)
{
	pid_t		proc;
	int			out_fd;
	int			in_fd;
	int			status;

	if (cmd->builtin == 1)
		return (exec_builtin(data, cmd));
	in_fd = input(cmd, data, STDIN_FILENO);
	if (in_fd == -1)
		return (data->my_errno);
	out_fd = output(cmd, data);
	if (out_fd == -1)
		return (data->my_errno);
	proc = fork();
	if (proc == -1)
		return (errno);
	else if (proc == 0)
		exit(exec_command(data, cmd, envp));
	signals_parent();
	waitpid(proc, &status, 0);
	if (cmd->prev != NULL)
		close(cmd->prev->fd[1]);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	execute(t_data *data, t_cmd *cmd)
{
	char	**envlist;
	int		stdinfd;
	int		stdoutfd;

	if (data->cmd != NULL)
	{
		data->my_errno = 0;
		g_signal = 0;
		cmd = data->cmd;
		if (setup_fds_envlist(&stdinfd, &stdoutfd, &envlist, data) == -1)
			return (errno);
		while (cmd->next != NULL)
		{
			data->my_errno = pipeline(data, cmd, envlist);
			signal_error(data);
			cmd = cmd->next;
			dup2(stdinfd, STDIN_FILENO);
			dup2(stdoutfd, STDOUT_FILENO);
		}
		data->my_errno = last_cmd(data, cmd, envlist);
		signal_error(data);
		free(envlist);
		reset_std_fds(stdinfd, stdoutfd);
	}
	return (data->my_errno);
}
