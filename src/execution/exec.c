/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/23 16:38:16 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input(t_cmd *cmd)
{
	t_content	*content;
	t_list		*in;
	int			in_fd;

	in = cmd->in;
	in_fd = STDIN_FILENO;
	while (in != NULL)
	{
		content = ((t_content *)(in->content));
		if (check_file(content->word, R_OK) == 0)
			in_fd = open(content->word, O_RDONLY, 0644);
		// else
		// 	in_fd = -1;
		in = in->next;
		if (in != NULL && in_fd != -1)
			close(in_fd);
	}
	ft_fprintf(2, "DEBUG: infd: %d\n", in_fd);
	dup2(in_fd, STDIN_FILENO);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	return (in_fd);
}

int	output(t_cmd *cmd)
{
	t_content	*content;
	t_list		*out;
	int			out_fd;

	out = cmd->out;
	out_fd = STDOUT_FILENO;
	while (out != NULL)
	{
		content = ((t_content *)(out->content));
		if (check_file(content->word, W_OK) != 2 && content->token == OUT)
			out_fd = open(content->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (check_file(content->word, W_OK) != 2 && content->token == APPEND)
			out_fd = open(content->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// else
		// 	out_fd = -1;
		out = out->next;
	}
	ft_fprintf(2, "DEBUG: outfd: %d\n", out_fd);
	dup2(out_fd, STDOUT_FILENO);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	return (out_fd);
}

void	pipeline(t_cmd	*cmd)
{
	pid_t	proc;
	int		in_fd;
	int		out_fd;

	in_fd = input(cmd);
	out_fd = output(cmd);
	if (pipe(cmd->fd) != 0)
		ft_fprintf(2, "DEBUG: Failed to pipe\n");
	proc = fork();
	if (proc == -1)
		return (((void)(ft_fprintf(2, "DEBUG: Failed to fork\n"))));
	else if (proc == 0) // child
	{
		close(cmd->fd[0]);
		dup2(cmd->fd[1], STDOUT_FILENO);
		close(cmd->fd[1]);
		exec_command(cmd);
	}
	else // parent
	{
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[1]);
		if (cmd->out != NULL)
			write_output();
		close(cmd->fd[0]);
	}
}

void	last_cmd(t_cmd	*cmd)
{
	pid_t	proc;
	int		out_fd;
	int		in_fd;

	out_fd = output(cmd);
	in_fd = input(cmd);
	proc = fork();
	if (proc == -1)
		return (((void)(ft_fprintf(2, "DEBUG: Failed to fork\n"))));
	else if (proc == 0)
		exec_command(cmd);
	else
		waitpid(proc, NULL, 0);
}

int	execute(t_cmd *cmdlst)
{
	t_cmd	*cmd;
	int		stdinfd;
	int		stdoutfd;

	if (cmdlst != NULL)
	{
		cmd = cmdlst;
		stdinfd = dup(STDIN_FILENO);
		stdoutfd = dup(STDOUT_FILENO);
		while (cmd->next != NULL)
		{
			pipeline(cmd);
			cmd = cmd->next;
		}
		last_cmd(cmd);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		dup2(stdinfd, STDIN_FILENO);
		dup2(stdoutfd, STDOUT_FILENO);
		close(stdinfd);
		close(stdoutfd);
	}
	return (0);
}
