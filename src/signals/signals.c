/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:25:30 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/22 20:38:12 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signal_interactive(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = 1;
		rl_done = 1;
		rl_replace_line("", 0);
	}
}

void	signal_ctrl_backslash(void)
{
	struct sigaction	ctrl_backslash;

	ctrl_backslash.sa_handler = SIG_IGN;
	ctrl_backslash.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_backslash.sa_mask);
	sigaction(SIGQUIT, &ctrl_backslash, NULL);
}

void	signal_ctrl_c(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = handle_signal_interactive;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	copy_termios_rem_c(struct termios *termios_mirror)
{
	struct termios	termios;

	tcgetattr(1, &termios);
	termios_mirror = &termios;
	termios.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &termios);
}

void	init_signals(struct termios *termios_mirror)
{
	copy_termios_rem_c(termios_mirror);
	signal_ctrl_c();
	signal_ctrl_backslash();
}
