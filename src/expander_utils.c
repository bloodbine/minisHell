/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/31 16:45:28 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	get_outer_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && get_closing_quote(&str[i] , '\''))
			return ('\'');
		if (str[i] == '\"' && get_closing_quote(&str[i] , '\"'))
			return ('\"');
		i++;
	}
	return (0);
}

int	dollar_pos(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (INT32_MIN);
}

int	my_strlen(char *str)
{
	int i;

	i = 0;
	while(str && str[i] != '\0')
		i++;
	return (i);
}

char	*my_strjoin(char *s1, char *s2)
{
	char	*nstring;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	nstring = malloc(my_strlen(s1) + my_strlen(s2) + 1);
	if (!nstring)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		nstring[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
	{
		nstring[i] = s2[j];
		i++;
		j++;
	}
	nstring[i] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (nstring);
}

int	get_seq(char *str, char **seq)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if(str[i] == '$' || str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	*seq = ft_substr(str, 0, i);
	return (i);
}