LIBRARY = library.a

COMPILER = gcc

SRCS = utils.c

MAIN = main.c

NAME = philo

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME): $(LIBRARY) $(MAIN)
	$(COMPILER) $(CFLAGS) $^ -o $@

%.o: %.c
	$(COMPILER) $(CFLAGS) -c $^

$(LIBRARY): $(OBJS)		
		ar rcs $(LIBRARY) $(OBJS)

clean:
	rm -rf $(OBJS) $(LIBRARY)

all: $(NAME)

.PHONY: clean fclean re all

fclean: clean
	rm -rf $(NAME)

re: fclean all