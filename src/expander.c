/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/31 17:16:02 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_env_var(char *str)
{
	char	*expanded;
	char	*temp;
	char	*seq;
	int		pos;
	int		i;
	
	i = 0;
	expanded = NULL;
	pos = dollar_pos(str);
	//printf("str: %s \n", str);
	if (pos < 0)
		return (str);
	while (pos >= 0) //aendern wegen folgenden zeichen nache env var bsp. $USER"test 
	{
		expanded = my_strjoin(expanded, ft_substr(str, i, pos - i));
		pos += get_seq(&str[pos + 1], &seq);
		temp = ft_substr(getenv(seq), 0, my_strlen(getenv(seq)));
		i = pos + 1;
		free(seq);
		expanded = my_strjoin(expanded, temp);
		//printf("exp: %s  i: %d\n", expanded, i);
		pos += dollar_pos(&str[i]);
	}
	temp = ft_substr(&str[i], 0, my_strlen(&str[i]));
	expanded = my_strjoin(expanded, temp);
	free(str);
	return (expanded);
}

char	*remove_outer_quotes(char *str, char quotes)
{
	int		i;
	int		j;
	char	*new;
	int		count;
	
	i = 0;
	j = 0;
	count = 0;
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

char	*expand(char *str, char quotes)
{
	int i = 0;
	int j = 0;
	int count = 0;
	char *sub = NULL;
	
	while(str[i] != '\0')
	{
		if (quotes == 0)
		{
			sub = my_strjoin(sub, expand_env_var(ft_substr(str, i, ft_strlen(str) - i)));
			break ;
		}
		if (str[i] == quotes)
		{
			if (!count)
			{
				sub = my_strjoin(sub, expand_env_var(ft_substr(str, j, i - j)));
				j = i;
			}
			count++;
		}
		if (count == 2 && quotes == '\"')
		{
			sub = my_strjoin(sub, expand_env_var(remove_outer_quotes(ft_substr(str, j, i - j + 1), quotes)));
			count = 0;
			j = i + 1;
			quotes = get_outer_quotes(&str[j]);
		}
		if (count == 2)
		{
			sub = my_strjoin(sub,remove_outer_quotes(ft_substr(str, j, i - j + 1), quotes));
			j = i + 1;
			quotes = get_outer_quotes(&str[j]);
			count = 0;
		}
		i++;
	}
	free(str);
	return (sub);
}

void rm_quotes(void *data)
{
	char	quotes;
	t_content *content = (t_content *)data;

	if (!content->word)
		return ;
	quotes = get_outer_quotes(content->word);
	content->word = expand(content->word, quotes); //change because of memory handling
}