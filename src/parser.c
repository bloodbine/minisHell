/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/14 12:05:57 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_content(void *data)
{
    t_content *content = (t_content *)data;
    printf("	%s(%d)", content->word, content->token);
}

void	fill_redir(t_cmd *cmd, t_content *l)
{
	char	*word;

	word = my_strcpy(l->word);
	if (l->token == OUT)
	{
		ft_lstadd_back(&(cmd->out), ft_lstnew(init_content(word)));
		((t_content *)(ft_lstlast(cmd->out)->content))->token = OUT;
	}
	else if (l->token == IN)
	{
		ft_lstadd_back(&(cmd->in), ft_lstnew(init_content(word)));
		((t_content *)(ft_lstlast(cmd->in)->content))->token = IN;
	}
	else if (l->token == APPEND)
	{
		ft_lstadd_back(&(cmd->out), ft_lstnew(init_content(word)));
		((t_content *)(ft_lstlast(cmd->out)->content))->token = APPEND;
	}
	else if (l->token == HEREDOC)
	{
		ft_lstadd_back(&(cmd->in), ft_lstnew(init_content(word)));
		((t_content *)(ft_lstlast(cmd->in)->content))->token = HEREDOC;
	}
	else
		free (word);
}

void	fill_cmd_struct(t_list *lex, t_cmd *cmd, int *i, int *argument)
{
	t_content	*l;
	
	l = ((t_content *)(lex->content));
	if (l->token == WORD)
	{
		if (!(cmd->args[0]))
			cmd->args[0] = my_strcpy(l->word);
		else if (!(*argument) && l->word[0] == '-')
		{
			cmd->args[1] = my_strjoin(cmd->args[1], &(l->word[*i - 1]), 1);
			*i = 1;
		}
		else
		{
			cmd->args[*i] = my_strcpy(l->word);
			*argument = 1;
		}
		(*i)++;
	}
	fill_redir(cmd, l);
	set_builtin(cmd);
}

void	build_cmds(t_list *lex, t_cmd **cmd)
{	
	int	i;
	int	argument;
	
	argument = 0;
	i = 0;
	if (!lex)
		return ;
	add_newnode_back(cmd, ft_lstsize(lex));
	while (lex)
	{
		if (((t_content *)(lex->content))->token == PIPE)
		{
			fill_cmd_struct(lex, *cmd, &i, &argument);
			add_newnode_back(cmd, ft_lstsize(lex));
			argument = 0;
			i = 0;
		}
		fill_cmd_struct(lex, *cmd, &i, &argument);
		lex = lex->next;
	}
	// printf("char *args[]:");
	// while (*((*cmd)->args))
	// {
	// 	printf("	\"%s\"", *((*cmd)->args));
	// 	((*cmd)->args)++;
	// }
	// printf("\n");
	// if((*cmd)->in)
	// 	printf("token:%d	%s\n", ((t_content *)((*cmd)->in->content))->token, ((t_content *)((*cmd)->in->content))->word);
	// if((*cmd)->out)
	// 	printf("token:%d	%s\n", ((t_content *)((*cmd)->out->content))->token, ((t_content *)((*cmd)->out->content))->word);	
}

void print_cmds(t_cmd *cmd)
{

	while (cmd && cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		printf("char **args:");
		while(*cmd->args)
		{
			printf("	%s", *(cmd->args));
			(cmd->args)++;
		}
		printf("\n");
		printf("in:");
		ft_lstiter(cmd->in, print_content);
		printf("\n");
		printf("out:");
		ft_lstiter(cmd->out, print_content);
		printf("\n");
		cmd = cmd->next;
	}
}

t_cmd	*parse(t_list *lex)
{
	t_cmd	*cmd;

	cmd = NULL;
	ft_lstiter(lex, expander);
	//ft_lstiter(lex, print_content);
	build_cmds(lex, &cmd);
	ft_lstclear(&lex, clear_content);
	print_cmds(cmd);
	return (cmd);
}
