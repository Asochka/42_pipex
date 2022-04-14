NAME			=		pipex
SRCS 			= 		main.c utils.c parsing.c pipex.c
OBJ 			=		$(SRCS:%.c=%.o)
CFLAGS 			= 		-Wall -Wextra -Werror
CC				=		gcc

ANOTHER_SRC		= 		ft_strlen.c ft_putendl_fd.c ft_strjoin.c ft_split.c ft_strncmp.c

LIBFT_PATH		=		libft/
LIBFT			=		$(LIBFT_PATH)libft.a
LIBFT_SRC 		= 		$(addprefix ./libft/, $(ANOTHER_SRC))
LIBFT_HEADER 	= 		./libft/libft.h
LIBFT_OBJS 		= 		$(LIBFT_SRC:.c=.o)
HEAD			=		pipex.h

all 			: 		$(NAME) $(LIBFT)

$(LIBFT)		: 		$(LIBFT_SRC) $(LIBFT_HEADER) $(LIBFT_OBJS) 
						make -s -C $(LIBFT_PATH)

$(NAME)		 	:		$(OBJ) $(LIBFT) 
						$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

%.o 			: 		%.c	Makefile $(HEAD) $(LIBFT_HEADER) ./libft/Makefile
						$(CC) $(CFLAGS) -c $< -o $@

clean 			: 
						@make -s -C $(LIBFT_PATH) clean
						@rm -f $(OBJ)

fclean 			: 		clean
						@make -s -C $(LIBFT_PATH) fclean
						@rm -f $(NAME)

re 				: 		fclean all

.PHONY			: 		all clean fclean re