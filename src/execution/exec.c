/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/19 11:09:39 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input(t_cmd *cmd)
{
	t_list	*in;
	int		fd;

	in = cmd->in;
	fd = STDIN_FILENO;
	if (in == NULL)
		return (fd);
	while (in != NULL)
	{
		if (fd != STDIN_FILENO && in->next != NULL)
			close(fd);
		if (check_file(((t_content *)(in->content))->word, R_OK) == 0)
			fd = open(((t_content *)(in->content))->word, O_RDONLY, 0644);
		else if (in->next == NULL)
			fd = -1;
		in = in->next;
	}
	if (fd != -1 && fd != STDIN_FILENO)
		dup2(STDIN_FILENO, fd);
	return (fd);
}

int	output(t_cmd *cmd)
{
	t_list	*out;
	int		fd;

	out = cmd->out;
	fd = STDOUT_FILENO;
	if (out == NULL)
		return (fd);
	while (out != NULL)
	{
		if (fd != STDOUT_FILENO && out->next != NULL)
			close(fd);
		if (check_file(((t_content *)(out->content))->word, W_OK) != 2)
		{
			if (((t_content *)(out->content))->token == APPEND)
				fd = open(((t_content *)(out->content))->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (((t_content *)(out->content))->token == OUT)
				fd = open(((t_content *)(out->content))->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (out->next == NULL)
				fd = -1;
		}
		out = out->next;
	}
	if (fd != -1 && fd != STDOUT_FILENO)
		dup2(STDOUT_FILENO, fd);
	return (fd);
}

void	exec(t_cmd	*cmd)
{
	pid_t	pid;
	int		fdpipe[2];
	int		in_fd;
	int		out_fd;
	char	*line;

	if (pipe(fdpipe) != 0)
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(fdpipe[0]);
		out_fd = output(cmd);
		dup2(fdpipe[1], STDOUT_FILENO);
		if (out_fd == -1)
			exit (1);
		exec_command(cmd);
	}
	else
	{
		close(fdpipe[1]);
		in_fd = input(cmd);
		dup2(fdpipe[0], STDIN_FILENO);
		if (in_fd == -1)
			return ;
		if (cmd->next != NULL)
			waitpid(pid, NULL, 0);
		while (1)
		{
			line = get_next_line(fdpipe[0]);
			if (line == NULL)
				break ;
			write(STDOUT_FILENO, line, ft_strlen(line));
		}
	}
}

int	execute(t_cmd *cmds)
{
	t_cmd	*cmd;
	int		fdstdin;
	int		fdstdout;

	fdstdin = dup(STDIN_FILENO);
	fdstdout = dup(STDOUT_FILENO);
	cmd = cmds;
	while (cmd != NULL)
	{
		exec(cmd);
		cmd = cmd->next;
	}
	dup2(fdstdin, STDIN_FILENO);
	dup2(fdstdout, STDOUT_FILENO);
	return (0);
}
