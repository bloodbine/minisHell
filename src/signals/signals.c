/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:25:30 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/07 02:24:49 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signal_interactive(int signal)
{
	if (signal == SIGINT)
	{
		rl_done = 1;
		g_signal = 1;
		//rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
	}
}

void	init_signals(void)
{
	signal(SIGINT, handle_signal_interactive);
	signal(SIGQUIT, SIG_IGN);
}
