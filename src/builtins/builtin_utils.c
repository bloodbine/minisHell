/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:21:58 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/04 16:48:30 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_pwd(t_list *l_envp, char *path)
{
	t_envp	*content;
	char	*pwd;
	char	**old;

	old = NULL;
	pwd = NULL;
	while (l_envp)
	{
		content = (t_envp *)(l_envp->content);
		if (ft_strncmp(content->word, "PWD", 4))
		{
			pwd = my_strcpy(content->word);
			free (content->word);
			content->word = my_strcpy(path);
		}
		if (ft_strncmp(content->word, "OLDPWD", 7))
			old = &content->word;
		l_envp = l_envp->next;
	}
	free(*old);
	*old = pwd;
}

void	print_env(void *data)
{
	t_envp	*content;

	content = (t_envp *)data;
	if (content->status)
		printf("%s\n", (char *)data);
}

void	toggle_env_var(char *arg, t_list *l_envp)
{
	t_envp	*content;

	while (l_envp)
	{
		content = (t_envp *)(l_envp->content);
		if (ft_strncmp(content->word, arg, ft_strlen(arg) + 1))
		{
			if (!content->status)
				content->status = 1;
			else
				content->status = 0;
			break ;
		}
		l_envp = l_envp->next;
	}
}
