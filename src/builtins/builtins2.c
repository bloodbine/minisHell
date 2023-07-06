/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 12:19:04 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/06 19:29:13 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	charcheck(char *string, int i, int id)
{
	id = 0;
	if (string[i] == '=' && i == 0)
		return (1);
	if (string[i] < '0' || string[i] > 'z')
		return (1);
	if (string[i] < '9' && string[i] < 'A' && id == 1)
		return (1);
	return(0);
}

int	env_validity_check(char **args)
{
	int	id;
	int	i;
	int	j;

	id = 0;
	i = 0;
	j = -1;
	while (args[++i] != NULL)
	{
		while (args[i][++j] != '\0')
		{
			if (args[i][j] == '=')
				id = 1;
			if (charcheck(args[i], j, id) == 1)
			{
				ft_fprintf(2, "minishell: %s: '%s': not a valid identifier\n", args[0], args[i]);
				exit(1);
			}
		}
		j = -1;
	}
	return (0);
}

int	my_export(char **args, t_data *data)
{
	t_list	*env;
	int		i;

	if (env_validity_check(args) == 1)
		return (1);
	i = 0;
	env = NULL;
	if (args == NULL || args[1] == NULL)
		return (1);
	while (args[++i] != NULL)
	{
		if (ft_strchr(args[i], '='))
		{
			env = check_exist_env(data, args[i]);
			if (env == NULL)
				ft_lstadd_front(&data->l_envp, ft_lstnew(init_content_envp(args[i])));
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
		else
			return (1);
	}
	return (0);
}