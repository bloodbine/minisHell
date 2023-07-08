/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/08 14:06:42 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/wait.h>

int	input(t_cmd *cmd, t_data *data)
{
	t_content	*content;
	t_list		*in;
	int			in_fd;

	in = cmd->in;
	in_fd = STDIN_FILENO;
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

	in_fd = input(cmd, data);
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
	{
		close(cmd->fd[0]);
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
		exit(exec_command(data, cmd, envp));
	}
	close(cmd->fd[1]);
	dup2(cmd->fd[0], STDIN_FILENO);
	if (cmd->out != NULL)
		write_output(STDIN_FILENO, STDOUT_FILENO);
	waitpid(proc, &status, WNOHANG);
	if (WIFEXITED(status))
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
	in_fd = input(cmd, data);
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
	waitpid(proc, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (cmd->prev != NULL)
		close(cmd->prev->fd[1]);
	return (0);
}

int	execute(t_data *data)
{
	t_cmd	*cmd;
	char	**envlist;
	int		stdinfd;
	int		stdoutfd;

	if (data->cmd != NULL)
	{
		data->my_errno = 0;
		cmd = data->cmd;
		stdinfd = dup(STDIN_FILENO);
		stdoutfd = dup(STDOUT_FILENO);
		if (stdinfd == -1 || stdoutfd == -1)
			return (errno);
		envlist = convert_env(data->l_envp);
		while (cmd->next != NULL)
		{
			data->my_errno = pipeline(data, cmd, envlist);
			// ft_fprintf(2, "DEBUG: %d\n", data->my_errno);
			if (data->my_errno != 0)
			{
				reset_std_fds(stdinfd, stdoutfd);
				return (data->my_errno);
			}
			cmd = cmd->next;
			dup2(stdinfd, STDIN_FILENO);
			dup2(stdoutfd, STDOUT_FILENO);
		}
		if (data->my_errno == 0)
			data->my_errno = last_cmd(data, cmd, envlist);
		// ft_fprintf(2, "DEBUG: %d\n", data->my_errno);
		// if (data->my_errno > 2)
		// 	perror("minishell");
		g_signal = data->my_errno;
		free(envlist);
		reset_std_fds(stdinfd, stdoutfd);
	}
	return (data->my_errno);
}
