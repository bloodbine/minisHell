/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:33:04 by ffederol          #+#    #+#             */
/*   Updated: 2023/06/30 17:06:19 by ffederol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# ifndef INT32_MIN
#  define INT32_MIN -2147483648
# endif

# include <signal.h>
# include <errno.h>

typedef enum e_token
{
	PIPE = 1,
	OUT = 2,
	APPEND = 3,
	IN = 4,
	HEREDOC = 5,
	WORD = 6
}			t_tok;

typedef enum e_quote
{
	NO_QUOTE = 0,
	S_QUOTE = 1,
	D_QUOTE = 2
}			t_quote;

typedef struct s_content
{
	char	*word;
	t_tok	token;
}			t_content;

typedef struct s_envp
{
	char	*word;
	int		status;
}			t_envp;

typedef struct s_lexdata
{
	int		i;
	int		len;
	int		start;
	int		redir;
	char	*str;
	t_quote	quote;
}			t_lexdata;

typedef struct s_expdata
{
	t_list	*l_envp;
	int		i;
	int		start;
	int		count;
	char	*sub;
	char	quotes;
}			t_expdata;

typedef struct s_cmd
{
	char	**args;  //for execve
	char	**envp;
	t_list	*in;
	t_list	*out;
	int		builtin;
	int		idx;
	int		fd[2];
	struct	s_cmd	*next;
	struct	s_cmd	*prev;
}			t_cmd;

void		init_signals(void);
void		handle_interrupt(int signal);
int			get_closing_quote(char *lptr, char quote);
int			get_len(char *lptr, int i);
t_list		*get_substrings(char *lptr);
t_list		*lex(char *lptr, t_list *l_envp);
int			is_token(char *str);
int			get_tokens(t_list **token, t_lexdata *l_data);
t_list		*tokenize(t_list *substring, t_lexdata *l_data);
char		get_outer_quotes(char *str);
char		*rm_quotes(char *str, char quotes);
void		expander(t_list *lex, t_list *l_envp);
t_cmd		*parse(t_list *lex, t_list *l_envp);
t_content	*init_content(char *str);
char		*my_strcpy(char *str);
int			add_newnode_back(t_cmd **cmd, int lstsize);
void		init_newnode(t_cmd *new, int lstsize);
char		*exp_env_var(char *str, t_list *l_envp);
char		*expand(char *str, t_expdata *exp_data);
int			dollar_pos(char *str);
int			my_strlen(char *str);
char		*my_strcpy(char *str);
char		*my_strjoin(char *s1, char *s2, int id);
int			get_seq(char *str, char **seq);
t_quote		toggle_quote(char *str, t_quote quote);
void		clear_str(void *data);
void		clear_content(void *data);
void		add_token(t_lexdata *l_data, t_list **token);
void		add_word(t_lexdata *l_data, t_list **token);
void		set_builtin(t_cmd *cmd);
int			heredoc(char *delim, t_list *l_envp);
char		*my_getenv(char *var, t_list *l_envp);
void 		clear_cmdlst(t_cmd **cmd);
char		**init_args(int lstsize);
void		clear_args(char **args);
t_cmd		*get_last_node(t_cmd *cmd);
t_cmd		*get_first_node(t_cmd *cmd);
void		init_newnode(t_cmd *new, int lstsize);

#endif
