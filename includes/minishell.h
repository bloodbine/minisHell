/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:17:16 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/06 12:03:22 by gpasztor         ###   ########.fr       */
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
	int		my_errno;
}			t_data;

# include "builtins.h"
# include "exec.h"

void	cpy_envp(t_list **l_envp, char **envp);

#endif
