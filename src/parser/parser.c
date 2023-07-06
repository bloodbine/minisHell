/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:24 by ffederol          #+#    #+#             */
/*   Updated: 2023/07/07 00:13:33 by ffederol         ###   ########.fr       */
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

int	check_echo(char **args, char **word, int *argument, int *j)
{
	int	i;

	i = 1;
	if (ft_strncmp(*args, "echo", 5) || ft_strncmp(*args, "/bin/echo", 10))
	{
		while (word[0][i] == 'n')
			i++;
		if (word[0][i] != '\0')
		{
			*argument = 1;
			args[*j] = my_strcpy(word[0]);
			return (1);
		}
		else 
		{
			if(args[1] && !ft_strncmp(*args, "echo", 5))
				return (*j = 1, 1);
			if(args[1] && !ft_strncmp(*args, "/bin/echo", 10))
			{
				args[*j] = my_strcpy(word[0]);
				return (1);	
			}
			free(word[0]);
			word[0] = my_strcpy("-n");
		}
	}
	return (0);	
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
			if (!check_echo(cmd->args, &l->word, argument, i))
			{
				cmd->args[1] = my_strjoin(cmd->args[1], &(l->word[*i - 1]), 1);
				*i = 1;
			}
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

	set_vars(&i, &argument);
	if (((t_content *)(lex->content))->token == PIPE)
		return (0);
	add_newnode_back(cmd, ft_lstsize(lex));
	while (lex)
	{
		if (((t_content *)(lex->content))->token == PIPE)
		{
			if (!lex->next || \
					((t_content *)(lex->next->content))->token == PIPE)
				return (0);
			if (!((t_content *)(lex->next->content))->word)
				return (-1);
			add_newnode_back(cmd, ft_lstsize(lex));
			set_vars(&i, &argument);
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
	//ft_lstiter(lex, print_content);
	expander(lex, l_envp);
	// if (g_signal == 1)
	// {
	// 	ft_lstclear(&lex, clear_content);
	// 	return (NULL);
	// }
	//ft_lstiter(lex, print_content);
	test = build_cmds(lex, &cmd);
	if (test <= 0)
	{
		clear_cmdlst(&cmd);
		write(2, "Minishell: syntax error near unexpected token ", 46);
		if (test == -1)
			write(2, "`newline'\n", 10);
		else
			write(2, "`|'\n", 4);
		g_signal = 2;
	}
	ft_lstclear(&lex, clear_content);
	//print_cmds(cmd);
	return (get_first_node(cmd));
}
