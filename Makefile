NAME	= philo

OBJDIR	= obj/
SRCDIR	= src/

SRC		=	

SRCOBJ	= $(patsubst %.c, $(OBJDIR)%.o, $(SRC))

CC		= cc
RMF		= rm -f
RMDIR	= rmdir
CFLAGS	= -Wall -Wextra -Werror

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRCOBJ)
	$(CC) $(SRCOBJ) $(CFLAGS) -o $(NAME)

libmake:
	@git submodule update --init --recursive --remote
	@cd $(MAKE) -c includes/libft
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

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re libmake check_brew