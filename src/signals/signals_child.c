/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:16:37 by gpasztor          #+#    #+#             */
/*   Updated: 2023/07/22 17:48:17 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_ctrl_c_child(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = SIG_DFL;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	signal_ctrl_backslash_child(void)
{
	struct sigaction	ctrl_backslash;

	ctrl_backslash.sa_handler = SIG_DFL;
	ctrl_backslash.sa_mask = SA_RESTART;
	sigemptyset(&ctrl_backslash.sa_mask);
	sigaction(SIGQUIT, &ctrl_backslash, NULL);
}

void	init_signals_child(struct termios *termios_mirror)
{
	tcsetattr(1, TCSAFLUSH, termios_mirror);
	signal_ctrl_c_child();
	signal_ctrl_backslash_child();
}
