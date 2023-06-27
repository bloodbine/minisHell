/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/27 02:46:47 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_content(void *data)
{
	t_content	*content;
	
	content = (t_content *)data;
	printf("	%s(%d)\n", content->word, content->token);
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

int	build_cmds(t_list *lex, t_cmd **cmd)
{	
	int	i;
	int	argument;

	argument = 0;
	i = 0;
	if (((t_content *)(lex->content))->token == PIPE)
		return (write(2, "Minishell: syntax error near unexpected token `|'\n", 50), 0);
	add_newnode_back(cmd, ft_lstsize(lex));
	while (lex)
	{
		if (((t_content *)(lex->content))->token == PIPE)
		{
			if (!lex->next || ((t_content *)(lex->next->content))->token == PIPE)
				return (write(2, "Minishell: syntax error near unexpected token `|'\n", 50), 0);
			if (!((t_content *)(lex->next->content))->word)
				return (-1);
			fill_cmd_struct(lex, *cmd, &i, &argument);
			add_newnode_back(cmd, ft_lstsize(lex));
			argument = 0;
			i = 0;
		}
		else if (!((t_content *)(lex->content))->word)
			return (-1);
		fill_cmd_struct(lex, *cmd, &i, &argument);
		lex = lex->next;
	}
	return (1);
}

void	print_cmds(t_cmd *cmd)
{
	cmd = get_first_node(cmd);
	char **temp;

	while (cmd)
	{
		printf("char **args:");
		temp = cmd->args;
		while (*temp)
		{
			printf("	%s", *temp);
			temp++;
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

t_cmd	*parse(t_list *lex, t_list *l_envp)
{
	t_cmd	*cmd;
	int		test;
	
	cmd = NULL;
	if (!lex)
		return (NULL);
	expander(lex, l_envp);
	if (g_signal == 1)
	{
		ft_lstclear(&lex, clear_content);
		return (NULL);
	}
	// ft_lstiter(lex, print_content);
	test = build_cmds(lex, &cmd);
	if(test <= 0)
	{
		clear_cmdlst(&cmd);
		if (test == - 1)
			write(2, "Minishell: syntax error near unexpected token `newline'\n", 56);
		g_signal = 2;
	}
	ft_lstclear(&lex, clear_content);
	//print_cmds(cmd);
	return (get_first_node(cmd));
}
