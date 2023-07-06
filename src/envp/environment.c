/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:53:32 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/06 19:07:12 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*my_getenv(char *var, t_list *l_envp)
{
	t_envp	*content;

	if (!ft_strncmp(var, "?", 2))
		return (ft_itoa(g_signal));
	else if (var[0] == ' ' || var[0] == '\0')
		return (my_strcpy("$"));
	while (l_envp)
	{
		content = ((t_envp *)(l_envp->content));
		if (!ft_strncmp(var, (content->word), \
				ft_strlen(var)) && content->status)
		{
			if ((content->word)[ft_strlen(var)] == '=')
				return (my_strcpy(content->word + ft_strlen(var) + 1));
		}
		l_envp = l_envp->next;
	}
	return (NULL);
}

t_envp	*init_content_envp(char *str)
{
	t_envp	*content;

	content = malloc(sizeof(t_content));
	if (!content)
		return (NULL);
	content->word = my_strcpy(str);
	content->status = 1;
	return (content);
}

void	cpy_envp(t_list **l_envp, char **envp)
{
	while (*envp)
	{
		ft_lstadd_back(l_envp, ft_lstnew(init_content_envp(*envp)));
		envp++;
	}
}
