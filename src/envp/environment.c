/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:53:32 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/27 15:40:58 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (!ft_strncmp(var, "?", 2))
		return (ft_itoa(g_signal));
	else if (var[0] == ' ' || var[0] == '\0')
		return ("$");
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
