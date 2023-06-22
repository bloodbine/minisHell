/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/22 22:40:34 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <termios.h>

void init_data(t_data *data)
{
	data->cmd = NULL;
}

void my_event_hook(void) {}

void init(t_data *data, char **envp)
{
	init_signals();
	init_data(data);
	cpy_envp(envp);
	rl_catch_signals = 0;
	rl_event_hook = (rl_hook_func_t *)my_event_hook;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*lptr;
	t_data	data;
	
	if (argc != 1 || argv[1] != NULL)
		return (write(2, "No Arguments allowed\n", 21), 0);
	init(&data, envp);
	//env();
	while (1)
	{
		lptr = readline("$ > ");
		if (!lptr)
		{
			printf("\x1b[A$ > exit\n");
			exit (1);
		}
		g_envp->content = "0";
		if(lptr[0] != '\0')
			add_history(lptr);
		data.cmd = parse(lex(lptr));
		free(lptr);
	}
	rl_clear_history();
	ft_lstclear(&g_envp, clear_str);
	return (0);
}
