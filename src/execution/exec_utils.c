/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:53:05 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/04 16:58:40 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_file(char *file, int check)
{
	if (check == W_OK)
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) == -1)
		{
			ft_fprintf(2, "minishell: %s: Permission denied\n", file);
			errno = EPERM;
			return (1);
		}
	}
	else if (check == R_OK)
	{
		if (access(file, F_OK == 1))
		{
			ft_fprintf(2, "minishell: %s: No such file or directory\n", file);
			errno = ENOENT;
			return (1);
		}
		else if (access(file, R_OK == -1))
		{
			ft_fprintf(2, "minishell: %s: Permission denied\n", file);
			errno = EPERM;
			return (2);
		}
	}
	return (0);
}

int	check_exist_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s: Command not found\n", cmd);
		return (1);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s: Permission denied\n", cmd);
		return (2);
	}
	return (0);
}

char	*check_paths(char *cmd, char **envp)
{
	char	**path_list;
	char	*ncmd;
	int		i;

	path_list = ft_split(get_path_env(envp), ':');
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

int	count_cmds(t_cmd *cmdlst)
{
	t_cmd	*cmd;
	int		cnt;

	cmd = cmdlst;
	cnt = 0;
	while (cmd != NULL)
	{
		cnt += 1;
		cmd = cmd->next;
	}
	return (cnt);
}

int	exec_command(t_data *data, t_cmd *cmd, char **envp)
{
	char	*ncmd;

	data = NULL;
	// if (cmd->builtin == 1)
	// 	exec_child_builtin(data, cmd->args[0], cmd->args);
	if (!ft_strchr(cmd->args[0], '/'))
	{
		ncmd = check_paths(ft_strjoin("/", cmd->args[0]), envp);
		if (ncmd != NULL)
		{
			if (execve(ncmd, cmd->args, envp) == -1)
				exit(errno);
		}
	}
	else if (check_exist_access(cmd->args[0]) == 0)
	{
		if (execve(cmd->args[0], cmd->args, envp) == -1)
			exit(errno);
	}
	exit(EXIT_FAILURE);
}
