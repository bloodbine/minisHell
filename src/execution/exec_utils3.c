/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:21:08 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/22 11:11:20 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_fds_envlist(int *in_fd, int *out_fd, char ***elist, t_data *data)
{
	*in_fd = dup(STDIN_FILENO);
	if (*in_fd == -1)
		return (-1);
	*out_fd = dup(STDOUT_FILENO);
	if (*out_fd == -1)
		return (-1);
	*elist = convert_env(data->l_envp);
	if (*elist == NULL)
		return (-1);
	return (0);
}

int	handle_special(char *cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd, "~", 2) == 0)
	{
		ft_fprintf(2, "minishell: %s: is a directory\n");
		exit(126);
	}
	if (ft_strncmp(cmd, "..", 3) == 0 || ft_strncmp(cmd, "", 1) == 0)
	{
		ft_fprintf(2, "minishell: %s: command not found\n", cmd);
		exit(127);
	}
	if (ft_strncmp(cmd, ".", 2) == 0)
	{
		ft_fprintf(2, "minishell: .: filename argument required\n");
		ft_fprintf(2, ".: usage . filename [arguments]\n");
		exit(2);
	}
	return (0);
}
