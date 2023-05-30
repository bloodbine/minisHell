/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/29 23:05:40 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void print_content(void *data) 
{
    t_content *content = (t_content *)data;
	printf("next\n");
    printf("token: %d   word: %s\n", content->token, content->word);

}
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

t_content *fill_content(char *str)
{
	t_content *content;

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

int	get_tokens(t_list **token, char *str)
{
	int	i;
	int	start;
	int	len;
	int	s_quote = 0;
	int	d_quote = 0;
	char *s;
	
	start = 0;
	i = 0;
	while (str[i] != '\0')
	{	// use enum typedef quote
		if (str[i] == '\'' && s_quote)
			s_quote = 0;
		if(str[i] == '\'' && get_closing_quote(&str[i], '\'') && !d_quote)
			s_quote = 1;
		if (str[i] == '\"' && d_quote)
			d_quote = 0;
		if(str[i] == '\"' && get_closing_quote(&str[i], '\"') && !s_quote)
			d_quote = 1;
		len = is_token(&str[i]);
		if(len != 0 && !d_quote && !s_quote)
		{
			if (len == -1)
				return (-1);
			s = ft_substr(str, start, i - start);
			if (s[0] != '\0')
				ft_lstadd_back(token, ft_lstnew(fill_content(ft_substr(str, start, i - start)))); 
			s = ft_substr(str, i, len);
			if (s[0] != '\0')
				ft_lstadd_back(token, ft_lstnew(fill_content(ft_substr(str, i, len))));
			i = i + len;
			start = i;
		}
		i++;
	}
	s = ft_substr(str, start, i - start);
	if (s[0] != '\0')
		ft_lstadd_back(token, ft_lstnew(fill_content(ft_substr(str, start, i - start))));
	return (0);
}

void clear_content(void *data)
{
	t_content *content = (t_content *)data;
	if (content->word)
		free(content->word);
}

void clear_str(void *data)
{
	char *content = (char *)data;
	if (content)
		free(content);
}

t_list *tokenize(t_list *substring)
{
	t_list	*token;
	
	token = NULL;
	while (substring)
	{
		if (get_tokens(&token, substring->content) == -1)
		{
			printf("Error");
			ft_lstclear(&token, clear_content);
			break ;
		}
		substring = substring->next;
	}
	ft_lstiter(token, print_content);
	ft_lstclear(&substring, clear_str);
	return token;
}

t_list *lex(char *lptr)
{
	t_list	*substring;
	t_list	*lex;
	
	substring = get_substrings(lptr);
	lex = tokenize(substring);
	return (lex);
}