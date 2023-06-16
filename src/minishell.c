/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/16 17:03:04 by gpasztor         ###   ########.fr       */
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
	while (1)
	{
		lptr = readline("$ >");
		data.cmd = parse(lex(lptr));
		printf("DEBUG: ARGS: %s\n", data.cmd->args[0]);
		data.cmd->envp = envp;
		execute(data.cmd);
		free(lptr);
	}
	return (0);
}
