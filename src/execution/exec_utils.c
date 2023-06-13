/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@42heilbronn.student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:53:05 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/09 20:12:45 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_infile(char *file, int *infd)
{
	if (file != NULL)
		*infd = open(file, O_RDONLY, 0644);
	else
		return (0);
	if (*infd == -1)
	{
		perror("minishell");
		*infd = open("/dev/null", O_RDONLY, 0644);
		if (*infd == -1)
			return (1);
	}
	dup2(*infd, STDIN_FILENO);
	return (1);
}

int	open_outfile(char *file, int *outfd)
{
	if (file != NULL)
		*outfd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		return (0);
	if (*outfd == -1)
	{
		perror("minishell");
		return (1);
	}
	return (1);
}
