/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/18 17:42:27 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_data(t_data *data)
{
	data->cmd = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*lptr;
	t_data	data;

	if (argc != 1 || argv[1] != NULL)
		return (write(2, "No Arguments allowed\n", 21), 0);
	init_data(&data);
	cpy_envp(envp);
	env();
	while (1)
	{
		lptr = readline("$ >");
		if(lptr[0] != '\0')
			add_history(lptr);
		data.cmd = parse(lex(lptr));
		free(lptr);
	}
	rl_clear_history();
	ft_lstclear(&g_envp, clear_str);
	return (0);
}
