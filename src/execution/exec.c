/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/19 15:13:32 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	input(t_cmd *cmd)
{
	t_content	*content;
	t_list		*in_list;
	int			fd;

	in_list = cmd->in;
	content = NULL;
	fd = STDIN_FILENO;
	while (in_list != NULL)
	{
		content = ((t_content *)(in_list->content));
		if (content->token == IN && check_file(content->word, R_OK) == 0)
			fd = open(content->word, O_RDONLY, 0644);
		if (content->token == HEREDOC && check_file(content->word, R_OK) == 0)
		{
			fd = open(content->word, O_RDONLY, 0644);
			unlink(content->word);
		}
		if (in_list->next == NULL)
		{
			if (fd == -1)
				break ;
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (fd != -1)
			close(fd);
		in_list = in_list->next;
	}
}

void	output(t_cmd *cmd)
{
	t_content	*content;
	t_list		*out_list;
	int			fd;

	out_list = cmd->out;
	content = NULL;
	fd = STDOUT_FILENO;
	while (out_list != NULL)
	{
		content = ((t_content *)(out_list->content));
		if (content->token == OUT && check_file(content->word, W_OK) != 2)
			fd = open(content->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (content->token == APPEND && check_file(content->word, W_OK) != 2)
			fd = open(content->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_list->next == NULL)
		{
			if (fd == -1)
				break ;
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (fd != -1)
			close(fd);
		out_list = out_list->next;
	}
}

void	write_output(void)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
	}
}

void	exec(t_cmd	*cmd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) != 0)
		return ;
	input(cmd);
	output(cmd);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec_command(cmd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (cmd->next == NULL)
			waitpid(pid, NULL, 0);
		write_output();
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
		ft_fprintf(2, "DEBUG: Exec loop\n");
		exec(cmd);
		cmd = cmd->next;
	}
	dup2(fdstdin, STDIN_FILENO);
	dup2(fdstdout, STDOUT_FILENO);
	return (0);
}
