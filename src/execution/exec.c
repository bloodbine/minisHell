/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/16 12:27:30 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input(t_cmd *cmd)
{
	t_content	*content;
	t_list		*in;
	int			fd;

	fd = 0;
	in = cmd->in;
	while (in != NULL)
	{
		if (cmd->in->next != NULL && fd != 0)
			close(fd);
		if (check_file(content->word, R_OK) == 0)
			fd = open(content->word, O_RDONLY, 0644);
		in = cmd->in->next;
	}
	if (cmd->idx == 0 && cmd->in == NULL)
		fd = open("/dev/null", O_RDONLY, 0644);
	return (fd);
}

int	output(t_cmd *cmd)
{
	t_content	*content;
	t_list		*out;
	int			fd;

	fd = 1;
	out = cmd->out;
	content = NULL;
	while (out != NULL)
	{
		if (cmd->out->next != NULL && fd != 0)
			close(fd);
		content = (t_content *)(out->content);
		if (check_file(content->word, W_OK) == 0)
		{
			if (content->token == APPEND)
				fd = open(content->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd = open(content->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (cmd->next == NULL)
			return (-1);
		out = cmd->out->next;
	}
	return (fd);
}

int	exec_command(t_cmd *cmd)
{
	if (cmd->builtin == 1)
	{
		printf("DEBUG: builtin\n");
		exit(EXIT_SUCCESS);
	}
	if (check_exist_access(cmd->args[0]) == 0)
		execve(cmd->args[0], cmd->args, cmd->envp);
	exit(EXIT_FAILURE);
}

int	exec_pipeline(t_cmd	*cmd)
{
	pid_t	process;
	int		in;
	int		out;
	int		fd[2];

	in = input(cmd);
	out = output(cmd);
	if (pipe(fd) != 1)
		return (close(in), close(out), 1);
	process = fork();
	if (process == 0)
	{
		close(fd[0]);
		dup2(fd[1], in);
		if (((t_content *)(cmd->in->content))->token == HEREDOC)
			unlink(((t_content *)(cmd->in->content))->word);
		exec_command(cmd);
	}
	close(fd[1]);
	dup2(fd[0], out);
	if (cmd->next == NULL)
		waitpid(process, NULL, 0);
}

int	execute(t_cmd *cmds)
{
	t_cmd	*command;

	command = cmds;
	while (command != NULL)
	{
		if (exec_pipeline(command) != 0)
			return (1);
		command = command->next;
	}
}
