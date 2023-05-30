/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:33:04 by ffederol          #+#    #+#             */
/*   Updated: 2023/05/29 23:41:52 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

typedef enum e_token
{
	PIPE = 1,
	OUT = 2,
	APPEND = 3,
	IN = 4,
	HEREDOC = 5,
	WORD = 6
}			t_tok;

typedef struct s_content 
{
	char	*word;
	t_tok	token;
}			t_content;


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

int		get_closing_quote(char *lptr, char quote);
int		get_end(char *lptr, int i);
t_list	*get_substrings(char *lptr);
t_list	*lex(char *lptr);
int		allowed_sign(char c);
int		is_token(char *str);
int		get_tokens(t_list **token, char *str);
t_list 	*tokenize(t_list *substring);
char	get_outer_quotes(char *str);
char	*remove_outer_quotes(char *str, char quotes);
void	rm_quotes(void *data);
t_cmd 	*parse(t_list *lex);

#endif
