/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/27 15:40:42 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_closing_quote(char *lptr, char quote)
{
	int	i;

	i = 1;
	while (lptr[i] != '\0')
	{
		if (lptr[i] == quote)
			return (i);
		i++;
	}
	return (0);
}

t_quote	toggle_quote(char *str, t_quote quote)
{
	if (str[0] == '\'' && quote == S_QUOTE)
		return (NO_QUOTE);
	if (str[0] == '\'' && get_closing_quote(&str[0], '\'') && !quote)
		return (S_QUOTE);
	if (str[0] == '\"' && quote == D_QUOTE)
		return (NO_QUOTE);
	if (str[0] == '\"' && get_closing_quote(&str[0], '\"') && !quote)
		return (D_QUOTE);
	return (quote);
}

int	get_len(char *lptr, int i)
{
	t_quote	quote;

	quote = NO_QUOTE;
	while (lptr[i] != '\0')
	{
		quote = toggle_quote(&lptr[i], quote);
		if (lptr[i] == ' ' && !quote)
			return (i);
		i++;
	}
	return (i);
}

int	is_token(char *str)
{
	if (!(ft_strchr("|><", str[0])))
		return (0);
	if (str[0] == '|')
	{
		if (str[1] == '|') //|| str[-1] == '|')
			return (0);
		return (1);
	}
	if (str[1] == str[0]) //&& (!(ft_strchr("|><", str[2])) || str[2] == '\0'))
		return (2);
	// else if (str[1] == str[0])
	// 	return (3);
	return (1);
}
