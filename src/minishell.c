/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/27 20:32:59 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_parse *parse(t_lex *lex_data)
// {
	
// }

// t_cmd *get_cmd(t_parse *parse_data)
// {
	
	
// }
void print_str(void *data) {
    char *str = (char *)data;
	printf("next\n");
    printf("%s\n", str);
}
int main(void)
{
	char 	*lptr;
	//t_data	data;
	
	while (1)
	{
		lptr = readline("$ >");
		ft_lstiter(lex(lptr), print_str);
		//data.cmd = get_cmd(parse(lex(lptr)));
		free(lptr);
	}
	return (0);
}
