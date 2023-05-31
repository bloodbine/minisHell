/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:09:53 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/31 16:42:07 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*my_strcpy(char *str)
{
	size_t	i;
	char *new;
	
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

void init_newnode(t_cmd *new)
{
	new->cmd = NULL;
	new->opt = NULL;
	new->arg = "\0";
	new->in = NULL;
	new->out = NULL;
	new->builtin = NULL;
}

void	add_newnode_back(t_cmd **cmd)
{
	t_cmd	*new;
	
	while ((*cmd) && (*cmd)->next)
		*cmd = (*cmd)->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	init_newnode(new);
	new->next = NULL;
	new->cmd = NULL;
	new->idx = 0;
	if (*cmd)
	{
		(*cmd)->next = new;
		new->idx = (*cmd)->idx + 1;
	}
	*cmd = new;
}