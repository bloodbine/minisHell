/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/29 23:07:14 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_parse *parse(t_lex *lex_data)
// {
	
// }

// t_cmd *get_cmd(t_parse *parse_data)
// {
	
	
// }

int main(void)
{
	char 	*lptr;
	t_data	data;
	
	while (1)
	{
		lptr = readline("$ >");
		data.cmd = parse(lex(lptr));
		free(lptr);
	}
	return (0);
}
