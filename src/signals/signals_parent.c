/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:16:34 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/22 20:01:36 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signal_interactive_parent(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 1;
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_backslash_parent(int signal)
{
	if (signal == SIGQUIT)
	{
		g_signal = 3;
		write(1, "^\\Quit: 3\n", 11);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signal_ctrl_c_parent(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = handle_signal_interactive_parent;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	signal_ctrl_backslash_parent(void)
{
	struct sigaction	ctrl_backslash;

	ctrl_backslash.sa_handler = handle_backslash_parent;
	ctrl_backslash.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_backslash.sa_mask);
	sigaction(SIGQUIT, &ctrl_backslash, NULL);
}

void	signals_parent(void)
{
	signal_ctrl_c_parent();
	signal_ctrl_backslash_parent();
}
