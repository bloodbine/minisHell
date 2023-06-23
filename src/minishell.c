/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/23 22:37:33 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	my_event_hook(void)
{
}

void	init(t_data *data, char **envp)
{
	init_signals();
	data->cmd = NULL;
	cpy_envp(&(data->l_envp), envp);
	rl_catch_signals = 0;
	rl_event_hook = (rl_hook_func_t *)my_event_hook;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*lptr;
	t_data	data;

	g_signal = 0;
	if (argc != 1 || argv[1] != NULL)
		return (write(2, "No Arguments allowed\n", 21), 0);
	init(&data, envp);
	//env(data.l_envp);
	while (1)
	{
		lptr = readline("$ > ");
		if (!lptr)
		{
			printf("\x1b[A$ > exit\n");
			break ;
		}
		if (lptr[0] != '\0')
			add_history(lptr);
		data.cmd = parse(lex(lptr, data.l_envp), data.l_envp);
		free(lptr);
	}
	clear_cmdlst(&(data.cmd));
	rl_clear_history();
	ft_lstclear(&data.l_envp, clear_str);
	return (0);
}
