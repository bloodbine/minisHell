/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:25:30 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/27 19:09:02 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
}
