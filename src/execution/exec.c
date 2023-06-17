/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/17 15:20:11 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input(t_cmd *cmd)
{
	t_content	*content;
	t_list		*in;
	int			fd;

	fd = STDIN_FILENO;
	in = cmd->in;
	content = NULL;
	while (in != NULL)
	{
		if (in->next != NULL && fd != 0)
			close(fd);
		content = (t_content *)(in->content);
		if (check_file(content->word, R_OK) == 0)
			fd = open(content->word, O_RDONLY, 0644);
		in = in->next;
	}
	return (fd);
}

int	output(t_cmd *cmd)
{
	t_content	*content;
	t_list		*out;
	int			fd;

	fd = STDOUT_FILENO;
	out = cmd->out;
	content = NULL;
	while (out != NULL)
	{
		if (out->next != NULL && fd != 0)
			close(fd);
		content = (t_content *)(out->content);
		if (check_file(content->word, W_OK) != 2)
		{
			if (content->token == APPEND)
				fd = open(content->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(content->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		out = out->next;
	}
	return (fd);
}

int	exec_pipeline(t_cmd	*cmd)
{
	pid_t	process;
	int		in;
	int		out;
	int		fd[2];
	char	*outcont;

	in = input(cmd);
	out = output(cmd);
	if (in == -1 || out == -1)
		return (1);
	if (pipe(fd) != 0)
		return (close(in), close(out), 1);
	process = fork();
	if (process == 0)
	{
		close(fd[0]);
		dup2(fd[1], out);
		exec_command(cmd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], in);
		if (cmd->next == NULL)
			waitpid(process, NULL, 0);
		while (1)
		{
			outcont = get_next_line(in);
			if (outcont == NULL)
				break ;
			write(out, outcont, ft_strlen(outcont));
			free(outcont);
		}
	}
	return (0);
}

int	execute(t_cmd *cmds)
{
	t_cmd	*command;

	command = cmds;
	while (command != NULL)
	{
		exec_pipeline(command);
		command = command->next;
	}
	rl_on_new_line();
	return (0);
}
