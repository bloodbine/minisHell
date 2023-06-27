NAME	= minishell

OBJDIR	= obj/
SRCDIR	= src/
INCDIR 	= -I ./include -I ./Users/$(USER)/.brew/opt/readline/include
LIBFT   = ./includes/libft/libft.a

MAIN	=	minishell

LEXER		=	lexer/lexer \
				lexer/lexer_utils \
				lexer/lexer_utils2

PARSER		=	parser/parser \
				parser/parser_utils

EXPANDER	=	expander/expander \
				expander/expander_utils

EXECUTION	=	execution/exec	\
				execution/exec_utils \
				execution/exec_utils2

MISC		=	misc/string_func

SOURCE		= $(MAIN) $(LEXER) $(PARSER) $(EXPANDER) $(EXECUTION) $(MISC)

SRC	= $(addprefix $(SRCDIR), $(addsuffix .c, $(SOURCE)))
OBJ	= $(addprefix $(OBJDIR), $(addsuffix .o, $(SOURCE)))

CC		= cc
RMF	= rm -f
RMRF	= rm -rf
RMDIR	= rmdir
CFLAGS	= -Wall -Wextra -Werror
FFLAGS	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(NAME): libmake $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT) -o $(NAME) $(FFLAGS)

libmake:
	git submodule update --init --recursive --remote
	$(MAKE) all bonus -C ./includes/libft
	# curl https://icanhazdadjoke.com/

# check_brew:
# 	@if [ `which brew` = "$(HOME)/.brew/bin/brew" ]; then \
# 		echo "Brew is installed"; \
# 		if [ `find $(HOME)/.brew/Cellar -name "libreadline.dylib" | wc -l` -gt 0 ]; then \
#     		echo "readline is installed"; \
# 		else \
# 			echo "No readline found"; \
# 			brew install readline; \
# 		fi; \
# 	else \
# 		echo "No Brew found"; \
# 		curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh; \
# 		brew install readline; \
# 	fi

clean:
	$(RMRF) $(OBJ)
	$(RMRF) $(OBJDIR)

fclean: clean
	$(RMF) $(NAME)
	make fclean -C ./includes/libft

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re libmake check_brew
