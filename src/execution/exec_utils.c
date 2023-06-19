/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:53:05 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/18 14:37:32 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_file(char *file, int check)
{
	if (access(file, F_OK) != 0 && check != W_OK)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", file);
		return (1);
	}
	if (access(file, check) != 0)
	{
		ft_fprintf(2, "minishell: %s: Permission denied\n", file);
		return (2);
	}
	return (0);
}

int	check_exist_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s: Command not found\n", cmd + 2);
		return (1);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s: Permission denied\n", cmd + 2);
		return (2);
	}
	return (0);
}

char	*check_paths(char *cmd)
{
	char	**path_list;
	char	*ncmd;
	int		i;

	path_list = ft_split(getenv("PATH"), ':');
	i = -1;
	ncmd = NULL;
	while (path_list[++i] != NULL)
	{
		ncmd = ft_strjoin(path_list[i], cmd);
		if (access(ncmd, F_OK) == 0)
		{
			if (access(ncmd, X_OK) == 0)
				break ;
		}
		free(ncmd);
		ncmd = NULL;
	}
	if (ncmd == NULL)
		ft_fprintf(2, "minishell: %s: Command not found\n", cmd);
	return (free(cmd), ncmd);
}

int	exec_command(t_cmd *cmd)
{
	char	*ncmd;

	if (!ft_strchr(cmd->args[0], '/'))
	{
		ncmd = check_paths(ft_strjoin("/", cmd->args[0]));
		if (ncmd != NULL)
			execve(ncmd, cmd->args, cmd->envp);
	}
	else if (check_exist_access(cmd->args[0]) == 0)
		execve(cmd->args[0], cmd->args, cmd->envp);
	exit(EXIT_FAILURE);
}
