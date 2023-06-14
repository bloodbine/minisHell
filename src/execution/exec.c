/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/14 13:03:03 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	input(t_cmd *cmd)
{
	t_list	*in;
	int		fd;

	fd = -2;
	in = cmd->in;
	while (in != NULL)
	{
		if (fd == -2)
		in = in->next;
	}
}

int	output(t_cmd *cmd)
{
	
}

int	exec_pipeline(t_cmd	*cmd)
{
	pid_t	process;
	int		in;
	int		out;
	int		fd[2];

	if (pipe(fd) != 0)
		return (1);
	process = fork();
	if (process == -1)
		return (1);
	if (process == 0)
	{
		close(fd[0]);
	}
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
