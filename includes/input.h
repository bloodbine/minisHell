/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:33:04 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/27 23:38:38 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

typedef enum e_token
{
	PIPE,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	REDIR_IN,
	HEREDOC
}			t_tok;

// typedef struct s_lex
// {
// 	char 	*word;
// 	int		idx;
// 	struct	t_lex	*next;
// }			t_lex;

typedef struct s_parse 
{
	char	*word;
	t_tok	token;
	int		idx;
}			t_parse;


typedef struct s_cmd
{
	char	*cmd;		
	char	*opt;
	char	*arg;
	char	*in;		// STD:IN; pipe; filename;
	char	*out;		// STD:OUT; pipe; filename;
	char	*builtin;	// NULL if cmd != builtin; cases: "echo", "cd", "pwd", "export", "unset", "env", "exit", NULL; if(builtin) then {use builtin} else {execve cmd};
	int		idx;
	struct	t_cmd	*next;
	struct	t_cmd	*prev;
}			t_cmd;

int		check_closing_quote(char *lptr, char quote);
int		get_end(char *lptr, int i);
t_list	*get_substrings(char *lptr);
t_list	*lex(char *lptr);
int		allowed_sign(char c);
int		is_token(char *str);
void	get_tokens(t_list **token, char *str);
t_list 	*tokenize(t_list *substring);

#endif
