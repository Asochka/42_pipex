NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

HEAD_FILE = libft.h

SRCS = ft_strlen.c ft_putendl_fd.c ft_strjoin.c ft_split.c ft_strncmp.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o : %.c $(HEAD_FILE) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re