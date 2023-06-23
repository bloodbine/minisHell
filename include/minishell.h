/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:17:16 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/23 16:44:08 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../includes/libft/libft.h"
# include "input.h"

int	g_signal;

typedef struct s_data
{
	t_cmd	*cmd;
	t_list	*l_envp;
}			t_data;

void	cpy_envp(t_list **l_envp, char **envp);
void	env(t_list *envp);
void	print_env(void *data);

#endif