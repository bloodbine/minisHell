/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/04 23:24:30 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*exp_env_var(char *str)
{
	char	*expanded;
	char	*seq;
	int		pos;
	int		i;

	i = 0;
	expanded = NULL;
	pos = dollar_pos(str);
	if (pos < 0)
		return (str);
	while (pos >= 0)
	{
		expanded = my_strjoin(expanded, ft_substr(str, i, pos - i), 2);
		pos += get_seq(&str[pos + 1], &seq);
		my_strcpy(getenv(seq));
		i = pos + 1;
		free(seq);
		expanded = my_strjoin(expanded, my_strcpy(getenv(seq)), 3);
		pos += dollar_pos(&str[i]);
	}
	expanded = my_strjoin(expanded, my_strcpy(&str[i]), 3);
	free(str);
	return (expanded);
}

char	*get_sub(char *str, t_expdata *exp)
{
	if (!exp->count)
	{
		exp->sub = my_strjoin(exp->sub, exp_env_var(str), 3);
		exp->start = exp->i;
	}
	if (exp->count == 1)
	{
		if (exp->quotes == '\"')
			exp->sub = my_strjoin(exp->sub, \
				exp_env_var(rm_quotes(str, exp->quotes)), 3);
		else
			exp->sub = my_strjoin(exp->sub, rm_quotes(str, exp->quotes), 3);
		exp->start = exp->i + 1;
		exp->count = -1;
	}
	return (exp->sub);
}

char	*expand(char *str, t_expdata *exp)
{
	int	s;
	int	len;

	len = ft_strlen(str);
	s = exp->start;
	while (str[exp->i] != '\0')
	{
		if (exp->quotes == 0)
			return (free(str), my_strjoin(exp->sub, \
				exp_env_var(ft_substr(str, exp->i, len - exp->i)), 3));
		if (str[exp->i] == exp->quotes)
		{
			if (!exp->count)
				exp->sub = get_sub(ft_substr(str, s, exp->i - s), exp);
			else if (exp->count == 1)
				exp->sub = get_sub(ft_substr(str, s, exp->i - s + 1), exp);
			s = exp->start;
			exp->count++;
			if (!exp->count)
				exp->quotes = get_outer_quotes(&str[s]);
		}
		exp->i++;
	}
	free(str);
	return (exp->sub);
}

void	init_expdata(t_expdata *data)
{
	data->count = 0;
	data->i = 0;
	data->start = 0;
	data->quotes = 0;
	data->sub = NULL;
}

void	expander(void *data)
{
	t_content	*content;
	t_expdata	exp;

	init_expdata(&exp);
	content = (t_content *)data;
	if (!content->word)
		return ;
	exp.quotes = get_outer_quotes(content->word);
	content->word = expand(content->word, &exp);
}
