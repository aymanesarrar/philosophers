COMPILER = gcc

SRCS = utils.c \
		utils2.c \
		list.c

MAIN = main.c

NAME = philo

CFLAGS = -Wall -Wextra -Werror


$(NAME): $(MAIN) $(SRCS)
	@echo "\033[32mCompiling ...\033[0m"
	$(COMPILER) $(CFLAGS) $^ -o $@

clean:
	@echo "\033[0;31mCleaning ...\033[0m"
	rm -rf $(NAME)

all: $(NAME)

.PHONY: clean fclean re all

norm:
	norminette $(SRCS) philo.h

fclean: clean
	rm -rf $(NAME)

re: fclean all