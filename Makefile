NAME	= minishell

OBJDIR	= obj/
SRCDIR	= src/
INCDIR 	= -I ./include -I ./Users/$(USER)/.brew/opt/readline/include
LIBFT   = ./includes/libft/libft.a

SRC		=	minishell.c \

SRCOBJ	= $(patsubst %.c, $(OBJDIR)%.o, $(SRC))

CC		= cc
RMF		= rm -f
RMDIR	= rmdir
CFLAGS	= -Wall -Wextra -Werror 
FFLAGS	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib

$(OBJDIR)%.o: $(SRCDIR)%.c libmake 
	mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(NAME): $(SRCOBJ)
	@$(CC) $(SRCOBJ) $(CFLAGS) $(LIBFT) -o $(NAME) $(FFLAGS)

libmake: check_brew
	@git submodule update --init --recursive --remote
	@$(MAKE) -C ./includes/libft
	@curl https://icanhazdadjoke.com/

check_brew:
	@if [ `which brew` = "$(HOME)/.brew/bin/brew" ]; then \
		echo "Brew is installed"; \
		if [ `find $(HOME)/.brew/Cellar -name "libreadline.dylib" | wc -l` -gt 0 ]; then \
    		echo "readline is installed"; \
		else \
			echo "No readline found"; \
			brew install readline; \
		fi; \
	else \
		echo "No Brew found"; \
		curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh; \
		brew install readline; \
	fi

clean:
	$(RMF) $(SRCOBJ)
	if [ -d "obj" ]; then $(RMDIR) $(OBJDIR); fi

fclean: clean
	$(RMF) $(NAME)
	make fclean -C ./includes/libft

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re libmake check_brew