/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:04:46 by gpasztor          #+#    #+#             */
/*   Updated: 2023/05/27 16:12:51 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*find_path(char *command)
{
	char	*env;
	char	**paths;
	char	*cmdpath;
	int		i;

	i = 0;
	env = getenv("PATH");
	if (env == NULL)
		return (free(command), NULL);
	paths = ft_split(env, ':');
	i = -1;
	while (paths[++i] != NULL)
	{
		cmdpath = ft_strjoin(paths[i], command);
		if (access(cmdpath, F_OK) == 0)
			break ;
		free(cmdpath);
		cmdpath = NULL;
	}
	i = -1;
	while (paths[++i] != NULL)
		free(paths[i]);
	return (free(paths), free(command), cmdpath);
}
