/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:33:04 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/27 15:26:19 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H



typedef struct s_cmd
{
	char			*cmd;
	char			*opt;
	char			*arg;
	char			*in;		// STD:IN; pipe; filename;
	char			*out;		// STD:OUT; pipe; filename;
	int				builtin;	// 1 if cmd == builtin;
	int				idx;
	struct t_cmd	*next;
	struct t_cmd	*prev;
}			t_cmd;

#endif
