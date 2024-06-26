/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/23 10:39:36 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	my_event_hook(void)
{
	return (0);
}

void	init(t_data *data, char **envp)
{
	init_signals(data->termios_mirror);
	g_signal = 0;
	data->cmd = NULL;
	data->l_envp = NULL;
	data->my_errno = 0;
	cpy_envp(&(data->l_envp), envp);
	rl_catch_signals = 0;
	rl_event_hook = (rl_hook_func_t *)my_event_hook;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*lptr;
	t_data	data;

	if (argc != 1 || argv[1] != NULL || getenv("USER") == NULL)
		return (0);
	init(&data, envp);
	while (1)
	{
		init_signals(data.termios_mirror);
		lptr = readline("$ > ");
		if (!lptr)
			break ;
		if (lptr[0] != '\0')
			add_history(lptr);
		data.cmd = parse(lex(lptr, &data), &data);
		free(lptr);
		data.my_errno = execute(&data, NULL);
		clear_cmdlst(&(data.cmd));
	}
	rl_clear_history();
	return (ft_lstclear(&(data.l_envp), clear_content), data.my_errno);
}
