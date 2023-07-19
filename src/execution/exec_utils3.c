/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 14:21:08 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/19 14:57:11 by gpasztor         ###   ########.fr       */
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
