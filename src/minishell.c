/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/26 17:47:57 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	char *lptr;
	
	while (1)
	{
		lptr = readline(NULL);
		printf("%s\n", lptr);
		free(lptr);
	}
	return (0);		
}
