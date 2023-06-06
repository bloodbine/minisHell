/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@42heilbronn.student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/05 19:05:41 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	// int		count;

	i = 0;
	j = 0;
	// count = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new)
	{
		printf("Error!");
	}
	while(str[i] != '\0')
	{
		if (str[i] != quotes)
			new[j++] = str[i];
		i++;
	}
	new[i] = '\0';
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
		if (str[i] == '$' || str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	*seq = ft_substr(str, 0, i);
	return (i);
}
