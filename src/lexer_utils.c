/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/27 23:36:22 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_closing_quote(char *lptr, char quote)
{
	while (*lptr != '\0')
	{
		if (*lptr == quote)
			return (1);
		lptr++;
	}
	return (0);
}

int get_end(char *lptr, int i)
{
	int s_quote;
	int d_quote;

	s_quote = 0;
	d_quote = 0;
	while (lptr[i] != '\0')
	{
		if (lptr[i] == '\'' && s_quote)
			s_quote = 0;
		else if (lptr[i] == '\'' && !d_quote)
			s_quote = check_closing_quote(&lptr[i + 1], '\'');
		if (lptr[i] == '\"' && d_quote)
			d_quote = 0;
		else if (lptr[i] == '\"' && !s_quote)
			d_quote = check_closing_quote(&lptr[i + 1], '\"');
		if (lptr[i] == ' ' && !s_quote && !d_quote)
			return (i);
		i++;
	}
	return (i);
}

int	allowed_sign(char c)
{
	if(c == '>' || c == '<' || c == '|')
		return (0);
	return (1);
}

int	is_token(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '<')
	{
		if (str[i + 1] == '<' && allowed_sign(str[i + 2]))
			return (2);
		else if ((str[i + 1] == '<' && !allowed_sign(str[i + 2])) || str[i + 1] == '>' || str[i + 1] == '|')
			return (-1);
		else 
			return (1);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] == '>' && allowed_sign(str[i + 2]))
			return (2);
		else if ((str[i + 1] == '>' && !allowed_sign(str[i + 2])) || str[i + 1] == '<' || str[i + 1] == '|')
			return (-1);
		else 
			return (1);
	}
	if (str[i] == '|')
	{
		if (str[i + 1] == '|' || str[i - 1] == '|')
			return (0);
		return (1);
	}
	return (0);
}