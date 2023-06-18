/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/18 12:39:23 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*lptr;
	t_data	data;

	if (argc != 1)
		return (1);
	argv = NULL;
	envp = NULL;
	while (1)
	{
		lptr = readline("$ >");
		printf("line test: %s\n", lptr);
		if (lptr != NULL)
		{
			data.cmd = parse(lex(lptr));
			if (data.cmd != NULL)
			{
				data.cmd->envp = envp;
				execute(data.cmd);
			}
		}
		free(lptr);
		lptr = NULL;
	}
	return (0);
}
