/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/22 20:43:01 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	get_outer_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && get_closing_quote(&str[i], '\''))
			return ('\'');
		if (str[i] == '\"' && get_closing_quote(&str[i], '\"'))
			return ('\"');
		i++;
	}
	return (0);
}

char	*rm_quotes(char *str, char quotes)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
	{
		write(2, "allocation failed", 17);
		return (NULL);
	}
	while (str[i] != '\0')
	{
		if (str[i] != quotes)
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

int	dollar_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (INT32_MIN);
}

int	get_seq(char *str, char **seq)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' || str[i] == ' ' || str[i] == '\'' \
				|| str[i] == '\"' || str[i] == '?' || str[i] == '/')
		{
			if (str[i] == '?')
				i++;
			break ;
		}
		i++;
	}
	*seq = ft_substr(str, 0, i);
	return (i);
}

int	expand_helper(char *str, t_expdata *exp, int s)
{
	if (!exp->count && exp->i && str[exp->i - 1] == '$')
		exp->sub = get_sub(ft_substr(str, s, exp->i - s - 1), exp);
	else if (!exp->count)
		exp->sub = get_sub(ft_substr(str, s, exp->i - s), exp);
	else if (exp->count == 1)
		exp->sub = get_sub(ft_substr(str, s, exp->i - s + 1), exp);
	return (exp->start);
}
