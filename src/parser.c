/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/04 23:25:34 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_content(void *data) 
// {
//     t_content *content = (t_content *)data;
// 	printf("next\n");
//     printf("token: %d   word: %s\n", content->token, content->word);

// }

void	fill_redir(t_cmd *cmd, t_content *l)
{
	if (l->token == OUT)
	{
		ft_lstadd_back(&(cmd->out), ft_lstnew(init_content(l->word)));
		((t_content *)(cmd->out->content))->token = OUT;
	}
	if (l->token == IN)
	{
		ft_lstadd_back(&(cmd->in), ft_lstnew(init_content(l->word)));
		((t_content *)(cmd->in->content))->token = IN;
	}
	if (l->token == APPEND)
	{
		ft_lstadd_back(&(cmd->out), ft_lstnew(init_content(l->word)));
		((t_content *)(cmd->out->content))->token = APPEND;
	}
}

void	fill_cmd_struct(t_list *lex, t_cmd *cmd, int *i)
{
	t_content	*l;

	l = ((t_content *)(lex->content));
	if (l->token == WORD)
	{
		if (!(cmd->args[0]))
			cmd->args[0] = my_strcpy(l->word);
		else if (!cmd->args[2] && l->word[0] == '-')
		{
			cmd->args[1] = my_strjoin(cmd->args[1], &(l->word[*i - 1]), 1);
			*i = 1;
		}
		else
			cmd->args[*i] = my_strcpy(l->word);
		(*i)++;
	}
	fill_redir(cmd, l);
}

void	build_cmds(t_list *lex, t_cmd **cmd)
{	
	int	i;

	i = 0;
	if (!lex)
		return ;
	add_newnode_back(cmd, ft_lstsize(lex));
	while (lex)
	{
		if (((t_content *)(lex->content))->token == PIPE)
		{
			fill_cmd_struct(lex, *cmd, &i);
			add_newnode_back(cmd, ft_lstsize(lex));
		}
		fill_cmd_struct(lex, *cmd, &i);
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

t_cmd	*parse(t_list *lex)
{
	t_cmd	*cmd;

	cmd = NULL;
	ft_lstiter(lex, expander);
	//ft_lstiter(lex, print_content);
	build_cmds(lex, &cmd);
	return (cmd);
}