/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/03 19:43:07 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	my_event_hook(void)
{
	return (0);
}

void	init(t_data *data, char **envp)
{
	init_signals();
	data->cmd = NULL;
	cpy_envp(&(data->l_envp), envp);
	rl_catch_signals = 0;
	//rl_event_hook = (rl_hook_func_t *)my_event_hook;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*lptr;
	t_data	data;

	g_signal = 0;
	if (argc != 1 && argv[1] == NULL && envp)
		return (write(2, "No Arguments allowed\n", 21), 1);
	init(&data, envp);
	while (1)
	{
		if (isatty(fileno(stdin)))
			lptr = readline("$ > ");
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			lptr = ft_strtrim(line, "\n");
			free(line);
		}	
		//lptr = readline("$ > ");
		if (lptr && !ft_strncmp(lptr, "exit", 5))
			break ;
		if (!lptr)
		{
			//printf("\x1b[A$ > exit\n");
			break ;
		}
		if (lptr[0] != '\0')
			add_history(lptr);
		data.cmd = parse(lex(lptr, data.l_envp), data.l_envp);
		free(lptr);
		execute(&data);
		clear_cmdlst(&(data.cmd));
	}
	rl_clear_history();
	ft_lstclear(&(data.l_envp), clear_content);
	return (g_signal);
}
