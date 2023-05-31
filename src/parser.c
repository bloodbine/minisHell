
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/31 16:45:28 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void print_content(void *data) 
// {
//     t_content *content = (t_content *)data;
// 	printf("next\n");
//     printf("token: %d   word: %s\n", content->token, content->word);

// }

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
		ft_lstadd_back(&(cmd->out), ft_lstnew(init_content(((t_content *)(lex->content))->word)));
		((t_content *)(cmd->out->content))->token = OUT;
	}
	if (((t_content *)(lex->content))->token == IN)
	{
		ft_lstadd_back(&(cmd->in), ft_lstnew(init_content(((t_content *)(lex->content))->word)));
		((t_content *)(cmd->in->content))->token = IN;
	}
	if (((t_content *)(lex->content))->token == APPEND)
	{
		ft_lstadd_back(&(cmd->out), ft_lstnew(init_content(((t_content *)(lex->content))->word)));
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
	//ft_lstiter(lex, print_content);
	//build_cmds(lex, &cmd);
	return (cmd);
}
