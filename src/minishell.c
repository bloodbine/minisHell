/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/19 11:03:24 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*lptr;
	t_data	data;

	argv = NULL;
	if (argc != 1)
		return (1);
	while (1)
	{
		lptr = readline("$ >");
		ft_fprintf(2, "DEBUG: line:%s\n", lptr);
		if (lptr != NULL && lptr[0] != '\0')
			add_history(lptr);
		if (lptr != NULL)
			data.cmd = parse(lex(lptr));
		free(lptr);
		lptr = NULL;
		if (data.cmd != NULL)
		{
			data.cmd->envp = envp;
			execute(data.cmd);
			data.cmd = NULL;
		}
		rl_on_new_line();
	}
	rl_clear_history();
	return (0);
}
