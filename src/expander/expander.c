/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/30 16:09:55 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*exp_env_var(char *str, t_list *l_envp)
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
		expanded = my_strjoin(expanded, my_strcpy(my_getenv(seq, l_envp)), 3);
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
		exp->sub = my_strjoin(exp->sub, exp_env_var(str, exp->l_envp), 3);
		exp->start = exp->i;
	}
	else if (exp->count == 1)
	{
		if (exp->quotes == '\"')
			exp->sub = my_strjoin(exp->sub, \
				exp_env_var(rm_quotes(str, exp->quotes), exp->l_envp), 3);
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
	int	len;

	len = ft_strlen(str);
	s = exp->start;
	while (str[exp->i] != '\0')
	{
		if (exp->quotes == 0)
		{
			exp->sub = my_strjoin(exp->sub, exp_env_var \
				(ft_substr(str, exp->i, len - exp->i), exp->l_envp), 3);
			break ;
		}
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

void	expander(t_list *lex, t_list *l_envp)
{
	t_content	*content;
	t_expdata	exp;

	exp.l_envp = l_envp;
	while (lex)
	{
		init_expdata(&exp);
		content = (t_content *)lex->content;
		if (!content->word)
			break ;
		exp.quotes = get_outer_quotes(content->word);
		if (content->token != HEREDOC)
			content->word = expand(content->word, &exp);
		else if (content->token == HEREDOC)
		{
			if (heredoc(content->word, l_envp) == -1)
			{
				write(2, "heredoc failed", 14);
				g_signal = errno;
				return ;
			}
			free(content->word);
			content->word = my_strcpy("heredoc");
		}
		lex = lex->next;
	}
}
