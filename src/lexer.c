/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/27 23:40:43 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// splits line on whitespaces. Ignore whitespaaces when in between quotes
t_list *get_substrings(char *lptr)
{
	t_list	*lexlst;
	int		start;
	int 	end;
	int 	i;
	
	i = 0;
	start = -1;
	lexlst = NULL;
	while(lptr[i] != '\0')
	{
		if(start == -1 && lptr[i] != ' ')
		{
			start = i;
			end = get_end(lptr, i);
			ft_lstadd_back(&lexlst, ft_lstnew(ft_substr(lptr, start, end - start)));
			i = end;
		}
		start = -1;
		i++;
	}
	return lexlst;
}

void	get_tokens(t_list **token, char *str)
{
	int	i;
	int	start;
	int	len;
	int	s_quote = 0;
	int	d_quote = 0;
	char *s;
	
	start = 0;
	i = 0;
	printf("start: %s\n", str);
	while (str[i] != '\0')
	{	
		if (str[i] == '\'' && s_quote)
			s_quote = 0;
		if(str[i] == '\'' && check_closing_quote(&str[i + 1], '\'') && !d_quote)
			s_quote = 1;
		if (str[i] == '\"' && d_quote)
			d_quote = 0;
		if(str[i] == '\"' && check_closing_quote(&str[i + 1], '\"') && !s_quote)
			d_quote = 1;
		len = is_token(&str[i]);
		//printf("s_quote %d    d_quote %d\n", s_quote, d_quote);
		if(len != 0 && !d_quote && !s_quote)
		{
			if (len == -1)
			{
				printf("Error\n");
				//free stuff ...
				return ;
			}
			s = ft_substr(str, start, i - start);
			if (s[0] != '\0')
			{
				ft_lstadd_back(token, ft_lstnew(ft_substr(str, start, i - start))); 
				// add token struct as content of list, not only substring as content
				printf("token: %s\n", ft_substr(str, start, i - start));
			}
			s = ft_substr(str, i, len);
			if (s[0] != '\0')
			{
				ft_lstadd_back(token, ft_lstnew(ft_substr(str, i, len)));
				printf("token: %s\n", ft_substr(str, i, len));
			}
			i = i + len;
			start = i;
		}
		i++;
	}
	s = ft_substr(str, start, i - start);
	if (s[0] != '\0')
	{
		ft_lstadd_back(token, ft_lstnew(ft_substr(str, i, i - start)));
		printf("token: %s\n", ft_substr(str, start, i - start));
	}
}

t_list *tokenize(t_list *substring)
{
	t_list	*token;
	
	token = NULL;
	while (substring)
	{
		get_tokens(&token, substring->content);
		substring = substring->next;
	}
	return NULL;
}

t_list *lex(char *lptr)
{
	t_list	*substring;
	t_list	*lex;
	
	substring = get_substrings(lptr);
	lex = tokenize(substring);
	return (lex);
}