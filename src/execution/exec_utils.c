/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:53:05 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/14 13:35:39 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_file(char *file, int check)
{
	if (access(file, F_OK) != 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return (1);
	}
	if (access(file, check) != 0)
	{
		printf("minishell: %s: Permission denied\n", file);
		return (2);
	}
	return (0);
}

int	check_exist_access(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		printf("minishell: %s: Command not found\n", cmd);
		return (1);
	}
	if (access(cmd, X_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd);
		return (2);
	}
	return (0);
}
