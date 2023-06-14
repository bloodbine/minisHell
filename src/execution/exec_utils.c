/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:53:05 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/13 16:49:41 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_infile(t_cmd *cmd)
{
	int	fd;


}

int	open_outfile(t_cmd *cmd)
{
	
}

int	check_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (0);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

int	check_exist_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		write(2, &cmd, ft_strlen(cmd));
		write(2, " :command not found\n", 20);
		return (1);
	}
	if (access(cmd, X_OK) == -1)
	{
		write(2, &cmd, ft_strlen(cmd));
		write(2, " :bad permissions\n", 18);
		return (1);
	}
	return (0);
}
