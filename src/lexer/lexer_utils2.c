/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/21 23:34:27 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_content	*init_content(char *str)
{
	t_content	*content;

	content = malloc(sizeof(t_content));
	if (!content)
	{
		// memory managen free()
		return (NULL);
	}
	content->word = NULL;
	content->token = WORD;
	if (!ft_strncmp(str, "|", 1))
		content->token = PIPE;
	else if (!ft_strncmp(str, ">>", 2))
		content->token = APPEND;
	else if (!ft_strncmp(str, "<<", 2))
		content->token = HEREDOC;
	else if (!ft_strncmp(str, ">", 1))
		content->token = OUT;
	else if (!ft_strncmp(str, "<", 1))
		content->token = IN;
	else
		content->word = my_strcpy(str);
	free (str);
	return (content);
}

void	add_token(t_lexdata *l_data, t_list **token)
{
	char	*s;

	s = ft_substr(l_data->str, l_data->i, l_data->len);
	if (s[0] != '\0' && !(l_data->redir))
	{
		if (s[0] != '|')
			l_data->redir = 1;
		ft_lstadd_back(token, ft_lstnew(init_content(s)));
	}
	else
		free (s);
}

void	add_word(t_lexdata *l_data, t_list **token)
{
	char	*s;

	s = ft_substr(l_data->str, l_data->start, l_data->i - l_data->start);
	if (s[0] != '\0' && !(l_data->redir))
		ft_lstadd_back(token, ft_lstnew(init_content(s)));
	else if (s[0] != '\0' && l_data->redir)
	{
		((t_content *)(ft_lstlast(*token)->content))->word = s;
		l_data->redir = 0;
	}
	else
		free (s);
}

void	clear_content(void *data)
{
	t_content	*content;

	content = (t_content *)data;
	if (content->word)
		free(content->word);
	free (content);
}

void	clear_str(void *data)
{
	char	*str;

	str = (char *)data;
	if (str)
		free(str);
}
