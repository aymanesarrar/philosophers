LIBRARY = library.a

SRCS = utils.c

MAIN = main.c

NAME = philo

CFLAGS = -Wall -Wextra -Werror

OBJS = utils.o

$(NAME): library.a main.c
	gcc $(CFLAGS) $(MAIN) $(LIBRARY) -o $(NAME)

$(OBJS): $(SRCS)
	gcc $(CFLAGS) -c $(SRCS)	

$(LIBRARY): $(OBJS)		
		ar rcs $(LIBRARY) $(OBJS)

clean:
	rm $(OBJS) $(LIBRARY)

all: $(NAME)

.PHONY: clean fclean re all

fclean: clean
	rm -rf $(NAME)

re: fclean all