/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:27:08 by gpasztor          #+#    #+#             */
/*   Updated: 2023/06/29 12:40:59 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char **argv)
{
	char	*line;
	int		i;

	i = 1;
	if (ft_strncmp(argv[i], "-n", 2) == 0)
	{
		while (argv[++i] != NULL)
		{
			line = ft_strtrim(argv[i]);
			write(STDOUT_FILENO, line, ft_strlen(line));
			free(line);
		}
	}
	else
	{
		i = 0;
		while (argv[++i] != NULL)
			write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
	}
}
