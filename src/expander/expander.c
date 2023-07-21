/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/21 19:08:22 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*exp_env_var(char *str, t_data *data)
{
	char	*expanded;
	char	*seq;
	int		pos;
	int		i;

	i = 0;
	expanded = NULL;
	seq = NULL;
	pos = dollar_pos(str);
	if (pos < 0)
		return (str);
	while (pos >= 0)
	{
		expanded = my_strjoin(expanded, ft_substr(str, i, pos - i), 3);
		pos += get_seq(&str[pos + 1], &seq);
		i = ++pos;
		expanded = my_strjoin(expanded, my_getenv(seq, data), 3);
		free(seq);
		pos += dollar_pos(&str[pos]);
	}
	expanded = my_strjoin(expanded, my_strcpy(&str[i]), 3);
	free(str);
	return (expanded);
}

char	*get_sub(char *str, t_expdata *exp)
{
	if (!exp->count)
	{
		exp->sub = my_strjoin(exp->sub, exp_env_var(str, exp->data), 3);
		exp->start = exp->i;
	}
	else if (exp->count == 1)
	{
		if (exp->quotes == '\"')
			exp->sub = my_strjoin(exp->sub, \
				exp_env_var(rm_quotes(str, exp->quotes), exp->data), 3);
		else
			exp->sub = my_strjoin(exp->sub, rm_quotes(str, exp->quotes), 3);
		exp->start = exp->i + 1;
		exp->count = -1;
	}
	else
		free (str);
	return (exp->sub);
}

char	*expand(char *str, t_expdata *exp)
{
	int	s;

	s = exp->start;
	while (str[exp->i] != '\0')
	{
		if (exp->quotes == 0)
		{
			exp->sub = my_strjoin(exp->sub, exp_env_var (ft_substr \
				(str, exp->i, ft_strlen(str) - exp->i), exp->data), 3);
			break ;
		}
		if (str[exp->i] == exp->quotes)
		{
			s = expand_helper(str, exp, s);
			exp->count++;
			if (!exp->count)
				exp->quotes = get_outer_quotes(&str[s]);
		}
		exp->i++;
	}
	free(str);
	return (exp->sub);
}

void	init_expdata(t_expdata *e_data, t_data *data)
{
	e_data->count = 0;
	e_data->i = 0;
	e_data->start = 0;
	e_data->quotes = 0;
	e_data->sub = NULL;
	e_data->data = data;
}

void	expander(t_list *lex, t_data *data, t_content *content)
{
	t_expdata	exp;

	while (lex)
	{
		init_expdata(&exp, data);
		content = (t_content *)lex->content;
		if (content->word)
		{
			exp.quotes = get_outer_quotes(content->word);
			if (content->token != HEREDOC)
				content->word = expand(content->word, &exp);
			else if (content->token == HEREDOC)
			{
				if (heredoc(&(content->word), data, 0) == -1)
				{
					write(2, "heredoc failed", 14);
					data->my_errno = errno;
					return ;
				}
				g_signal = 0;
			}
		}
		lex = lex->next;
	}
}
