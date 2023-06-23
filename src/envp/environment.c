/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:53:32 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/23 16:02:46 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env(void *data)
{
	printf("%s\n", (char *)data);
}

//builtin
void	env(t_list *l_envp)
{
	ft_lstiter(l_envp, print_env);
}

char	*my_getenv(char *var, t_list *l_envp)
{
	while (l_envp)
	{
		if (!ft_strncmp(var, (char *)(l_envp->content), ft_strlen(var)))
		{
			if (((char *)(l_envp->content))[ft_strlen(var)] == '=')
				return ((char *)(l_envp->content) + ft_strlen(var) + 1);
		}
		l_envp = l_envp->next;
	}
	return (NULL);
}

void	cpy_envp(t_list **l_envp, char **envp)
{
	while (*envp)
	{
		ft_lstadd_back(l_envp, ft_lstnew(my_strcpy(*envp)));
		envp++;
	}
}
