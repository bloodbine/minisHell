NAME	= minishell

OBJDIR	= obj/
SRCDIR	= src/
INCDIR 	= -I ./include -I /Users/$(USER)/.brew/opt/readline/include
LIBFT   = ./includes/libft/libft.a

MAIN	=	minishell

LEXER		=	lexer/lexer \
				lexer/lexer_utils \
				lexer/lexer_utils2

PARSER		=	parser/parser \
				parser/parser_utils

EXPANDER	=	expander/expander \
				expander/expander_utils \
				expander/expander_utils2 

EXECUTION	=	execution/exec	\
				execution/exec_utils \
				execution/exec_utils2

BUILTINS	=	builtins/builtins \
				builtins/builtins2 \
				builtins/builtin_utils

ENVP		=	envp/environment

SIGNALS		=	signals/signals

LISTFUNC	=	listfunc/double_linked_list

MISC		=	misc/string_func

SOURCE		= $(MAIN) $(LEXER) $(PARSER) $(EXPANDER) $(EXECUTION) $(BUILTINS) $(ENVP) $(SIGNALS) $(LISTFUNC) $(MISC)

SRC	= $(addprefix $(SRCDIR), $(addsuffix .c, $(SOURCE)))
OBJ	= $(addprefix $(OBJDIR), $(addsuffix .o, $(SOURCE)))

CC		= cc
RMF	= rm -f
RMRF	= rm -rf
RMDIR	= rmdir
CFLAGS	= -Wall -Wextra -Werror -g
FFLAGS	= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline 

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(NAME): libmake $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT) -o $(NAME) $(FFLAGS)

libmake:
	git submodule update --init --recursive --remote
	$(MAKE) all bonus -C ./includes/libft
	# curl https://icanhazdadjoke.com/

clean:
	$(RMRF) $(OBJ)
	$(RMRF) $(OBJDIR)

fclean: clean
	$(RMF) $(NAME)
	make fclean -C ./includes/libft

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re libmake check_brew
