/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/16 18:38:30 by gpasztor         ###   ########.fr       */
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
		if (cmd->in->next != NULL && fd != 0)
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
		out = out->next;
	}
	return (fd);
}

int	exec_command(t_cmd *cmd)
{
	char	*ncmd;

	ft_fprintf(2, "DEBUG: args: %s %s\n", cmd->args[0], cmd->args[1]);
	if (cmd->builtin == 1)
	{
		printf("DEBUG: builtin\n");
		exit(EXIT_SUCCESS);
	}
	else if (!ft_strchr(cmd->args[0], '/'))
	{
		ncmd = check_paths(ft_strjoin("/", cmd->args[0]));
		if (ncmd != NULL)
			execve(ncmd, cmd->args, cmd->envp);
	}
	// ft_fprintf(2, "DEBUG: checking existance and access of command\n");
	else if (check_exist_access(cmd->args[0]) == 0)
	{
		ft_fprintf(2, "DEBUG: attempting exec\n");
		execve(cmd->args[0], cmd->args, cmd->envp);
	}
	exit(EXIT_FAILURE);
}

int	exec_pipeline(t_cmd	*cmd)
{
	pid_t	process;
	int		in;
	int		out;
	int		fd[2];

	in = input(cmd);
	printf("DEBUG: input open\n");
	out = output(cmd);
	printf("DEBUG: output open\n");
	if (in == -1 || out == -1)
		return (1);
	printf("DEBUG: input and output success\n");
	if (pipe(fd) != 0)
		return (close(in), close(out), 1);
	ft_fprintf(2, "DEBUG: pipe open\n");
	process = fork();
	if (process == 0)
	{
		printf("DEBUG: child started\n");
		close(fd[0]);
		ft_fprintf(2, "DEBUG: child closed fd[0]\n");
		dup2(fd[1], in);
		ft_fprintf(2, "DEBUG: child duped fd[1]\n");
		exec_command(cmd);
		ft_fprintf(2, "DEBUG: failed to exec\n");
	}
	close(fd[1]);
	ft_fprintf(2, "DEBUG: parent closed fd[1]\n");
	dup2(fd[0], out);
	ft_fprintf(2, "DEBUG: parent duped fd[0]\n");
	if (cmd->next == NULL)
		waitpid(process, NULL, 0);
	// if (((t_content *)(cmd->in->content))->token == HEREDOC)
	// 	unlink(((t_content *)(cmd->in->content))->word);
	return (0);
}

int	execute(t_cmd *cmds)
{
	t_cmd	*command;

	command = cmds;
	while (command != NULL)
	{
		printf("DEBUG: entered loop\n");
		exec_pipeline(command);
		command = command->next;
	}
	printf("DEBUG: exited execution loop\n");
	return (0);
}
