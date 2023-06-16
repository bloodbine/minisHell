/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:09:53 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/14 15:25:57 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_builtin(t_cmd *cmd)
{
	if (!cmd->args[0])
		return ;
	if (!ft_strncmp(cmd->args[0], "echo", 4))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "cd", 2))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "pwd", 3))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "export", 6))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "unset", 5))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		cmd->builtin = 1;
	else if (!ft_strncmp(cmd->args[0], "exit", 4))
		cmd->builtin = 1;
}

char	**init_args(int lstsize)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (lstsize + 1));
	if (!new)
		return (NULL);
	while (i < lstsize)
	{
		new[i] = NULL;
		i++;
	}
	new[i] = NULL;
	return (new);
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

	while ((*cmd) && (*cmd)->next)
		*cmd = (*cmd)->next;
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
