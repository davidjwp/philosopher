CC			= gcc

CFLAGS		= -g3 -Werror -Wall -Wextra

NAME		= philo

SRCS		= init.c main.c parse.c utils.c activity.c

HEADER		= philosopher.h

OBJS		= $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -c $(CFLAGS) $< -o $@

dclean: clean
	rm -f $(DEBUG_OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all
