/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@42heilbronn.student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:41:48 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/06 11:01:24 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execpipeline(t_cmd *cmds)
{
	
}

int	pipe_child(t_cmd *cmds)
{
	
}

int	execone(t_cmd *cmds)
{
	char	*cmd;

	
}

int	execute(t_cmd *cmds)
{
	if (cmds->next == NULL)
	{
		if (execone(cmds) == 1)
			return (1);
	}
	else
	{
		if (execpipeline(cmds) == 1)
			return (1);
	}
	return (0);
}
