/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:53:05 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/22 17:26:37 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_file(t_data *data, char *file, int check)
{
	if (access(file, F_OK == -1))
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", file);
		data->my_errno = 1;
		return (1);
	}
	else if (access(file, check == -1))
	{
		ft_fprintf(2, "minishell: %s: Permission denied\n", file);
		data->my_errno = 1;
		return (2);
	}
	else if(access(file, X_OK) != -1)
	{
		ft_fprintf(2, "minishell: %s: Is a directory\n", file);
		data->my_errno = 1;
		return (3);
	}
	return (0);
}

int	check_exist_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", cmd + 1);
		exit(127);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_fprintf(2, "minishell: %s: Permission denied\n", cmd + 1);
		exit(126);
	}
	return (0);
}

char	*check_paths(char *cmd, char **envp)
{
	char	**path_list;
	char	*ncmd;
	int		i;

	path_list = ft_split(get_path_env(envp), ':');
	if (path_list != NULL)
		path_list[0] += 5;
	i = -1;
	ncmd = NULL;
	while (path_list[++i] != NULL)
	{
		ncmd = ft_strjoin(path_list[i], cmd);
		if (access(ncmd, X_OK) == 0)
			break ;
		free(ncmd);
		ncmd = NULL;
	}
	if (ncmd == NULL)
	{
		ft_fprintf(2, "minishell: %s: Command not found\n", cmd + 1);
		free(cmd);
		exit(127);
	}
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

	handle_special(data, cmd->args[0]);
	if (cmd->builtin == 1)
		exec_builtin(data, cmd);
	else if (!ft_strchr(cmd->args[0], '/'))
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
	exit(0);
}
