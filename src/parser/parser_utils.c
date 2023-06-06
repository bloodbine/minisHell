/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:09:53 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/04 20:23:59 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*my_strcpy(char *str)
{
	size_t	i;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**init_args(int lstsize)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (lstsize + 1));
	if (!new)
		return (NULL); //check for memoryhandling!!
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
	new->builtin = NULL;
	new->next = NULL;
	new->idx = 0;
}

void	add_newnode_back(t_cmd **cmd, int lstsize)
{
	t_cmd	*new;

	while ((*cmd) && (*cmd)->next)
		*cmd = (*cmd)->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	init_newnode(new, lstsize);
	new->prev = *cmd;
	if (*cmd)
	{
		(*cmd)->next = new;
		new->idx = (*cmd)->idx + 1;
	}
	*cmd = new;
}
