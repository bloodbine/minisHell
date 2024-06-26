/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:53:32 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/22 15:45:12 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*remove_double_spaces(char *str)
{
	int		i;
	int		j;
	char	*removed;
	int		space;

	space = 0;
	removed = malloc((ft_strlen(str) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == ' ')
			space++;
		else
			space = 0;
		if (space <= 1)
		{
			removed[j] = str[i];
			j++;
		}
		i++;
	}
	removed[i] = '\0';
	return (removed);
}

char	*my_getenv(char *var, t_data *data)
{
	t_envp	*content;
	char	*temp;
	t_list	*ptr_envp;

	ptr_envp = data->l_envp;
	if (!ft_strncmp(var, "?", 2))
		return (ft_itoa(data->my_errno));
	else if (var[0] == ' ' || var[0] == '\0')
		return (my_strcpy("$"));
	while (ptr_envp)
	{
		content = ((t_envp *)(ptr_envp->content));
		if (!ft_strncmp(var, (content->word), \
				ft_strlen(var)) && content->status)
		{
			if ((content->word)[ft_strlen(var)] == '=')
			{
				temp = remove_double_spaces(content->word + ft_strlen(var) + 1);
				return (temp);
			}
		}
		ptr_envp = ptr_envp->next;
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
