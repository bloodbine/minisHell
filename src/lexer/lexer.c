/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@42heilbronn.student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/06 11:00:06 by gpasztor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	print_content(void *data)
// {
// 	t_content	*content = (t_content *)data;
// 	printf("next\n");
// 	printf("token: %d   word: %s\n", content->token, content->word);
// }

// void	print_content1(void *data)
// {
//    	char	*content = (char *)data;
// 	printf("next\n");
//     printf("substr: %s\n", content);
// }

// splits line on whitespaces. Ignore whitespaaces when in between quotes
t_list	*get_substrings(char *lptr)
{
	t_list	*lexlst;
	int		end;
	int		i;

	i = 0;
	lexlst = NULL;
	while (lptr[i] != '\0')
	{
		if (lptr[i] != ' ')
		{
			end = get_len(lptr, i);
			ft_lstadd_back(&lexlst, ft_lstnew(ft_substr(lptr, i, end - i)));
			i = end;
		}
		i++;
	}
	return (lexlst);
}

int	get_tokens(t_list **token, t_lexdata *l_data)
{
	t_quote	quote;

	quote = NO_QUOTE;
	l_data->start = 0;
	l_data->i = 0;
	while (l_data->str[l_data->i] != '\0')
	{
		quote = toggle_quote(&(l_data->str[l_data->i]), quote);
		l_data->len = is_token(&(l_data->str[l_data->i]));
		if (l_data->len != 0 && !quote)
		{
			if (l_data->len == -1)
				return (-1);
			add_word(l_data, token);
			add_token(l_data, token);
			l_data->i = l_data->i + l_data->len;
			l_data->start = l_data->i;
			continue ;
		}
		l_data->i++;
	}
	add_word(l_data, token);
	return (0);
}

t_list	*tokenize(t_list *substring, t_lexdata *l_data)
{
	t_list	*token;

	token = NULL;
	// ft_lstiter(substring, print_content1);
	while (substring)
	{
		l_data->str = substring->content;
		if (get_tokens(&token, l_data) == -1)
		{
			printf("Error!\n");
			ft_lstclear(&token, clear_content);
			break ;
		}
		substring = substring->next;
	}
	//ft_lstiter(token, print_content);
	ft_lstclear(&substring, clear_str);
	return (token);
}

void	init_lex_data(t_lexdata **l_data)
{
	*l_data = malloc(sizeof(t_lexdata));
	if (!l_data)
		exit (1); //ERRORHANDLING!!!
	(*l_data)->i = 0;
	(*l_data)->len = 0;
	(*l_data)->redir = 0;
	(*l_data)->start = 0;
	(*l_data)->str = NULL;
	(*l_data)->quote = NO_QUOTE;
}

t_list	*lex(char *lptr)
{
	t_list		*substring;
	t_list		*lex;
	t_lexdata	*l_data;

	l_data = NULL;
	init_lex_data(&l_data);
	substring = get_substrings(lptr);
	lex = tokenize(substring, l_data);
	return (lex);
}
