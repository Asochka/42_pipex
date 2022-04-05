NAME		=	pipex

LIBFT_PATH	=	libft/

LIBFT		=	$(LIBFT_PATH)libft.a

SRCS		=	array_utils.c	cmd_call.c	cmd_process.c\
				error.c			get_path.c	pipes.c\
				pipex.c			main.c

SRCS_B		=	array_utils.c	cmd_call.c	cmd_process.c\
				error.c			get_path.c	pipes.c\
				here_doc.c		pipex_bonus.c	main_bonus.c\
				get_next_line/get_next_line.c	get_next_line/get_next_line_utils.c

OBJ			=	$(SRCS:%.c=%.o)

OBJ_B		=	$(SRCS_B:%.c=%.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

.PHONY		=	all clean fclean re bonus

all:	$(LIBFT) $(NAME)

bonus:	$(LIBFT)
	@make OBJ="$(OBJ_B)" all

$(LIBFT):
	make -s -C $(LIBFT_PATH)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -s -C $(LIBFT_PATH) clean
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	make -s -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re:	fclean all
