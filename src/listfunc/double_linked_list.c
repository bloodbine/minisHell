/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:27:15 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/04 16:49:45 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*get_first_node(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd && cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

t_cmd	*get_last_node(t_cmd *cmd)
{
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	init_newnode(t_cmd *new, int lstsize)
{
	new->args = init_args(lstsize);
	new->in = NULL;
	new->out = NULL;
	new->builtin = 0;
	new->next = NULL;
	new->idx = 0;
}

int	add_newnode_back(t_cmd **cmd, int lstsize)
{
	t_cmd	*new;

	*cmd = get_last_node(*cmd);
	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		write(2, "allocation failed \n", 19);
		return (-1);
	}
	init_newnode(new, lstsize);
	if (!new->args)
	{
		write(2, "allocation failed \n", 19);
		return (-1);
	}
	new->prev = *cmd;
	if (*cmd)
	{
		(*cmd)->next = new;
		new->idx = (*cmd)->idx + 1;
	}
	*cmd = new;
	return (0);
}

void	clear_cmdlst(t_cmd **cmd)
{
	if (!cmd || !(*cmd))
		return ;
	*cmd = get_last_node(*cmd);
	while (1)
	{
		clear_args((*cmd)->args);
		ft_lstclear(&(*cmd)->in, clear_content);
		ft_lstclear(&(*cmd)->out, clear_content);
		if ((*cmd)->prev)
			*cmd = (*cmd)->prev;
		else
			break ;
		free((*cmd)->next);
	}
	free(*cmd);
	*cmd = NULL;
}
