/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:09:53 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/31 05:40:07 by ffederol         ###   ########.fr       */
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

int	my_strlen(char *str)
{
	int i;

	i = 0;
	while(str && str[i] != '\0')
		i++;
	return (i);
}

char	*my_strjoin(char *s1, char *s2)
{
	char	*nstring;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	nstring = malloc(my_strlen(s1) + my_strlen(s2) + 1);
	if (!nstring)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		nstring[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
	{
		nstring[i] = s2[j];
		i++;
		j++;
	}
	nstring[i] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (nstring);
}

int	get_seq(char *str, char **seq)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if(str[i] == '$' || str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	*seq = ft_substr(str, 0, i);
	return (i);
}
//"$USER""1"
char	*expand_env_var(char *str)
{
	char	*expanded;
	char	*temp;
	char	*seq;
	int		pos;
	int		i;
	
	i = 0;
	expanded = NULL;
	pos = dollar_pos(str);
	if (pos < 0)
		return (str);
	while (pos >= 0) //aendern wegen folgenden zeichen nache env var bsp. $USER"test 
	{
		expanded = my_strjoin(expanded, ft_substr(str, i, pos - i));
		pos += get_seq(&str[pos + 1], &seq) + 1;
		temp = ft_substr(getenv(seq), 0, my_strlen(getenv(seq)));
		expanded = my_strjoin(expanded, temp);
		free(seq);
		pos += dollar_pos(&str[pos]);
		i = pos;
	}
	free(str);
	return (expanded);
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
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

char	*expand(char *str, char quotes)
{
	int i = 0;
	int j = 0;
	int count = 0;
	char *sub = NULL;
	
	while(str[i] != '\0')
	{
		if (quotes == 0)
		{
			sub = my_strjoin(sub, expand_env_var(ft_substr(str, i, ft_strlen(str) - i)));
			break ;
		}
		if (str[i] == quotes)
		{
			if (!count)
			{
				sub = my_strjoin(sub, expand_env_var(ft_substr(str, j, i - j)));
				j = i;
			}
			count++;
		}
		if (count == 2 && quotes == '\"')
		{
			sub = my_strjoin(sub, expand_env_var(remove_outer_quotes(ft_substr(str, j, i - j + 1), quotes)));
			count = 0;
			j = i + 1;
			quotes = get_outer_quotes(&str[j]);
		}
		if (count == 2)
		{
			sub = my_strjoin(sub,remove_outer_quotes(ft_substr(str, j, i - j + 1), quotes));
			j = i + 1;
			quotes = get_outer_quotes(&str[j]);
			count = 0;
		}
		i++;
	}
	free(str);
	return (sub);
}

void print_content(void *data) 
{
    t_content *content = (t_content *)data;
	printf("next\n");
    printf("token: %d   word: %s\n", content->token, content->word);

}

void rm_quotes(void *data)
{
	char	quotes;
	t_content *content = (t_content *)data;

	if (!content->word)
		return ;
	quotes = get_outer_quotes(content->word);
	content->word = expand(content->word, quotes); //change because of memory handling
}

void init_newnode(t_cmd *new)
{
	new->cmd = NULL;
	new->opt = NULL;
	new->arg = "\0";
	new->in = NULL;
	new->out = NULL;
	new->builtin = NULL;
}

void	add_newnode_back(t_cmd **cmd)
{
	t_cmd	*new;
	
	while ((*cmd) && (*cmd)->next)
		*cmd = (*cmd)->next;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return ;
	init_newnode(new);
	new->next = NULL;
	new->cmd = NULL;
	new->idx = 0;
	if (*cmd)
	{
		(*cmd)->next = new;
		new->idx = (*cmd)->idx + 1;
	}
	*cmd = new;
}

char	*my_strcpy(char *str)
{
	size_t	i;
	char *new;
	
	i = 0;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	fill_cmd(t_list *lex, t_cmd *cmd)
{
	char	*temp = NULL;
	
	if (!cmd->cmd && ((t_content *)(lex->content))->token == WORD)
	{
		cmd->cmd = my_strcpy(((t_content *)(lex->content))->word);
	}
		
	else if (cmd->cmd && cmd->arg[0] == '\0' && ((t_content *)(lex->content))->token == WORD && ((t_content *)(lex->content))->word[0] == '-')
	{
			if (!cmd->opt)
				cmd->opt = my_strcpy(((t_content *)(lex->content))->word);
			else
			{
				temp = cmd->opt;
				cmd->opt = ft_strjoin(temp, &((t_content *)(lex->content))->word[1]);
				//free(temp);	
			}
			
	}
	else if (cmd->cmd && ((t_content *)(lex->content))->token == WORD)
	{
		temp = cmd->arg;
		if (temp[0] != '\0')
			temp = ft_strjoin(temp, " "); //for spacec between single args
		cmd->arg = ft_strjoin(temp, ((t_content *)(lex->content))->word);
		//free(temp);	
	}
	if (((t_content *)(lex->content))->token == OUT)
	{
		ft_lstadd_back(&(cmd->out), ft_lstnew(fill_content(((t_content *)(lex->content))->word)));
		((t_content *)(cmd->out->content))->token = OUT;
	}
	if (((t_content *)(lex->content))->token == IN)
	{
		ft_lstadd_back(&(cmd->in), ft_lstnew(fill_content(((t_content *)(lex->content))->word)));
		((t_content *)(cmd->in->content))->token = IN;
	}
	if (((t_content *)(lex->content))->token == APPEND)
	{
		ft_lstadd_back(&(cmd->out), ft_lstnew(fill_content(((t_content *)(lex->content))->word)));
		((t_content *)(cmd->out->content))->token = APPEND;
	}
}

void	build_cmds(t_list *lex, t_cmd **cmd)
{	
	if (!lex)
		return ;
	add_newnode_back(cmd);
	while (lex)
	{
		if (((t_content *)(lex->content))->token == PIPE)
		{
			fill_cmd(lex, *cmd);
			add_newnode_back(cmd);
		}
		fill_cmd(lex, *cmd);
		lex = lex->next;
	}
	printf("cmd:	%s\n", (*cmd)->cmd);
	printf("opt:	%s\n", (*cmd)->opt);
	printf("arg:	%s\n", (*cmd)->arg);
	if((*cmd)->in)
		printf("%d:	%s\n", ((t_content *)((*cmd)->in->content))->token, ((t_content *)((*cmd)->in->content))->word);
	if((*cmd)->out)
		printf("%d:	%s\n", ((t_content *)((*cmd)->out->content))->token, ((t_content *)((*cmd)->out->content))->word);

		
}

t_cmd *parse(t_list *lex)
{
	t_cmd *cmd;

	cmd = NULL;
	ft_lstiter(lex, rm_quotes);
	ft_lstiter(lex, print_content);
	build_cmds(lex, &cmd);
	return (cmd);
}
