/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:17:16 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/22 00:57:11 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
#  include <readline/readline.h>
#  include <readline/history.h>
#  include <fcntl.h>
#  include "../includes/libft/libft.h"
#  include "input.h"
#  include "signals.h"


t_list *g_envp;

typedef struct s_data
{
	t_cmd	*cmd;
	//t_list	*l_envp; //only needed if not global
}			t_data;

void	cpy_envp(char **envp);
void	env(void);
void	print_env(void *data);

#endif
