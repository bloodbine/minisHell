/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:19:04 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/19 12:39:06 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	charcheck(char *string, int i)
{
	if (string[i] == '=' && i == 0)
		return (1);
	if ((string[i] < '0' || string[i] > 'z' \
			|| string[i] == '?' \
			|| string[i] == '^' \
			|| string[i] == '@' \
			|| string[i] == '-') && string[i] != ' ' && string[i] != '\t')
		return (1);
	return (0);
}

int	env_validity_check(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (args[++i] != NULL)
	{
		while (args[i][++j] != '\0')
		{
			if (charcheck(args[i], j) == 1)
			{
				ft_fprintf(2, "minishell: %s: '%s':", args[0], args[i]);
				ft_fprintf(2, " not a valid idetifier\n");
				return (1);
			}
		}
		j = -1;
	}
	return (0);
}

int	my_export(char **args, t_data *data, int i)
{
	t_list	*env;

	if (env_validity_check(args) == 1)
		return (1);
	if (args == NULL || args[1] == NULL)
		return (0);
	while (args[++i] != NULL)
	{
		if (ft_strchr(args[i], '='))
		{
			env = check_exist_env(data, args[i]);
			if (env == NULL)
			{
				env = ft_lstnew(init_content_envp(args[i]));
				ft_lstadd_front(&data->l_envp, env);
			}
			else
			{
				free(((t_envp *)(env->content))->word);
				((t_envp *)(env->content))->word = ft_strdup(args[i]);
				env = NULL;
			}
		}
	}
	return (0);
}

int	my_unset(char **args, t_data *data)
{
	t_list	*env;
	int		i;

	if (args[1] == NULL)
		return (0);
	if (env_validity_check(args) == 1)
		return (1);
	i = 0;
	env = NULL;
	if (args[1] == NULL)
		return (1);
	while (args[++i] != NULL)
	{
		args[i] = my_strjoin(args[i], "=", 1);
		env = check_exist_env(data, args[i]);
		if (env != NULL)
			((t_envp *)(env->content))->status = 0;
	}
	return (0);
}
