/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:17:16 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/08 23:36:57 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
#  include <readline/readline.h>
#  include <readline/history.h>
#  include "libft/libft.h"
#  include "input.h"
#  include <fcntl.h>

typedef struct s_data
{
	t_cmd	*cmd;
}			t_data;

#endif
