/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@42heilbronn.student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/06 11:01:02 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		content->word = str;
	return (content);
}

void	add_token(t_lexdata *l_data, t_list **token)
{
	char	*s;

	printf("test1\n");
	if (l_data->redir)
	{
		printf("test\n");
		printf("ERROR!\n"); // ERRORHANDLING
		exit (1);
	}	
	s = ft_substr(l_data->str, l_data->i, l_data->len);
	if (s[0] != '\0' && !(l_data->redir))
	{
		ft_lstadd_back(token, ft_lstnew(init_content(s)));
		if (s[0] != '|')
			l_data->redir = 1;
	}
}

void	add_word(t_lexdata *l_data, t_list **token)
{
	char	*s;

	s = ft_substr(l_data->str, l_data->start, l_data->i - l_data->start);
	if (s[0] != '\0' && !(l_data->redir))
		ft_lstadd_back(token, ft_lstnew(init_content(s)));
	else if (s[0] != '\0' && l_data->redir) //check first char "<>|"
	{
		((t_content *)(ft_lstlast(*token)->content))->word = s;
		l_data->redir = 0;
	}
}

void	clear_content(void *data)
{
	t_content	*content;

	content = (t_content *)data;
	if (content->word)
		free(content->word);
}

void	clear_str(void *data)
{
	char	*str;

	str = (char *)data;
	if (str)
		free(str);
}
