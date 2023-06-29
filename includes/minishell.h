/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:17:16 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/29 15:29:28 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include "../includes/libft/libft.h"
# include "input.h"
# include "exec.h"

int	g_signal;

typedef struct s_data
{
	t_cmd	*cmd;
	t_list	*l_envp;
	char 	**envp;
}			t_data;

void	cpy_envp(t_list **l_envp, char **envp);
void	env(t_list *envp);
void	print_env(void *data);
int		execute(t_data *data);
void	exec_builtin(t_data *data, char *cmd, char **argv);
int	exec_command(t_data *data, t_cmd *cmd, char **envp);

#endif
