/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/14 12:14:40 by gpasztor         ###   ########.fr       */
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
			i = end - 1;
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
			if (l_data->len == -1 || l_data->redir)
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
	t_list	*temp;

	temp = substring;
	token = NULL;
	// ft_lstiter(substring, print_content1);
	while (temp)
	{
		l_data->str = temp->content;
		if (get_tokens(&token, l_data) == -1)
		{
			write(2, "minishell: parse error near unexpected token ", 45);
			write(2, &l_data->str[l_data->i], 1); // ERRORHANDLING
			write(2, "\n", 1);
			ft_lstclear(&token, clear_content);
			ft_lstclear(&substring, clear_str);
			exit (1);
		}	
		temp = temp->next;
	}
	//ft_lstiter(token, print_content);
	ft_lstclear(&substring, clear_str);
	return (token);
}

void	init_lex_data(t_lexdata **l_data)
{
	*l_data = malloc(sizeof(t_lexdata));
	if (!l_data)
	{
		write(2, "allocation failed", 17);
		exit (1);
	}
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
	free (l_data);
	return (lex);
}
