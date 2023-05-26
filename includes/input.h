/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:33:04 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/26 17:53:47 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H



typedef struct s_cmd
{
	char	*cmd;
	char	*opt;
	char	*arg;
	char	*in;		// STD:IN; pipe; filename;
	char	*out;		// STD:OUT; pipe; filename;
	char	*builtin;	// NULL if cmd != builtin; 
	int		idx;
	struct	t_cmd	*next;
	struct	t_cmd	*prev;
}			t_cmd;

#endif
