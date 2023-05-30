/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:09:53 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/30 03:40:34 by ffederol         ###   ########.fr       */
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

int	get_seq(char *str, char **seq, char quotes)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if(str[i] == '$' || str[i] == ' ' || str[i] == quotes)
			break ;
		i++;
	}
	*seq = ft_substr(str, 0, i);
	return (i);
}

char	*expand_env_var(char *str, char quotes)
{
	char	*temp;
	char	*temp1;
	char	*expanded;
	char	*seq;
	int		pos;
	int		i;
	int 	hh;
	
	i = 0;
	expanded = ft_substr("\0", 0, 0);
	pos = dollar_pos(str);
	if (pos < 0)
		return (str);
	printf("pos: %d\n", pos);
	while (pos >= 0)
	{
		temp = ft_substr(str, i, pos - i);
		temp1 = expanded;
		expanded = ft_strjoin(temp1, temp);
		free(temp1);
		hh = get_seq(&str[pos + 1], &seq, quotes);
		pos += hh + 1;
		printf("seq: %s\n", seq);
		printf("temp %s\n", temp);
		temp1 = expanded;
		expanded = ft_strjoin(expanded, getenv(seq));
		printf("hh: %d\n", hh);
		if (str[hh + 2] == '\"')
			expanded = ft_strjoin(expanded, "\"");
		free(temp1);
		printf("expanded %s\n", expanded);
		free(temp);
		free(seq);
		temp = expanded;
		pos += dollar_pos(&str[pos]);
		i = pos;
		printf("pos: %d\n", pos);
	}
	free(str);
	return (expanded);
}

char	*expand(char *str, char quotes)
{
	int i = 0;
	int j = 0;
	int count = 0;
	char *sub = ft_substr("\0",0,0);
	char *temp;
	
	while(str[i] != '\0')
	{
		if (quotes == 0)
		{
			temp = sub;
			sub = ft_strjoin(temp, expand_env_var(ft_substr(str, j, ft_strlen(str) - j + 1), quotes));
			printf("%s\n", sub);
			free(temp);
			break ;
		}
		if (str[i] == quotes)
			count++;
		if (count == 2 && quotes == '\"')
		{
			temp = sub;
			sub = ft_strjoin(temp, expand_env_var(ft_substr(str, j, i - j + 1), quotes));
			printf("%s\n", sub);
			free(temp);
			count = 0;
			j = i + 1;
			quotes = get_outer_quotes(&str[j]);
		}
		if (count == 2)
		{
			temp = sub;
			sub = ft_strjoin(temp,ft_substr(str, j, i - j + 1));
			printf("%s\n", sub);
			free(temp);
			j = i + 1;
			quotes = get_outer_quotes(&str[j]);
			count = 0;
		}
		i++;
	}
	printf("%s\n", sub);
	return (sub);
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
		if (str[i] == quotes)
		{
			count++;
			if (count == 2)
				quotes = get_outer_quotes(&str[i + 1]);
			if (count > 2 && get_closing_quote(&str[i], quotes))
				count = 1;//quotewechsel einbinden
			else if (count > 2)
				new[j++] = str[i];
		}
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}



void rm_quotes(void *data)
{
	char	quotes;
	t_content *content = (t_content *)data;
	
	if (!content->word)
		return ;
	quotes = get_outer_quotes(content->word);
	content->word = expand(content->word, quotes); //change because of memory handling
	if (quotes == '\"' || quotes == '\'')
		content->word = remove_outer_quotes(content->word, quotes);
	printf("content: %s\n", content->word);
}

t_cmd *parse(t_list *lex)
{
	t_cmd *cmd;

	cmd = NULL;
	ft_lstiter(lex, rm_quotes);
	return (cmd);
}