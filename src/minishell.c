/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/18 13:04:31 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*lptr;
	t_data	data;

	while (1)
	{
		lptr = readline("$ >");
		if(lptr[0] != '\0')
			add_history(lptr);
		data.cmd = parse(lex(lptr));
		free(lptr);
		
	}
	rl_clear_history();
	return (0);
}
