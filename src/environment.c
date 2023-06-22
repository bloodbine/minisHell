/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:53:32 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/22 19:31:29 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_env(void *data)
{
   	char	*content = (char *)data;
    printf("%s\n", content);
}

void env()
{
	ft_lstiter(g_envp, print_env); //builtin
}

char *my_getenv(char *var)
{
	t_list	*l_temp;
	
	l_temp = g_envp;
	while (l_temp)
	{
		if (!ft_strncmp(var, (char *)(l_temp->content), ft_strlen(var)))
		{
			if(((char *)(l_temp->content))[ft_strlen(var)] == '=')
				return ((char *)(l_temp->content) + ft_strlen(var) + 1);
		}
		l_temp = l_temp->next;
	}
	return (NULL);
}

void cpy_envp(char **envp)
{
	g_envp = NULL;
	while (*envp)
	{
		ft_lstadd_back(&g_envp, ft_lstnew(my_strcpy(*envp)));
		envp++;
	}
	ft_lstadd_front(&g_envp, ft_lstnew("0"));
}
