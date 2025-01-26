NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MK = make

SRCS = main.c ft_free_error.c pipex_utils.c checking.c

S_BONUS = main_bonus.c get_next_line.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(S_BONUS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		$(MK) -C ./Libft
		$(CC) $(CFLAGS) $(OBJS) ./Libft/libft.a -o $(NAME)

bonus : $(BONUS_NAME)

$(BONUS_NAME) : $(OBJS_BONUS) ./Libft/libft.a
	$(CC) $(CFLAGS) $(OBJS_BONUS) ./Libft/libft.a -o $(BONUS_NAME)

./Libft/libft.a:
	$(MK) -C ./Libft

clean:
		$(MK) clean -C ./Libft
		${RM} ${OBJS} $(OBJS_BONUS)

fclean: clean
		$(MK) fclean -C ./Libft
		$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY:
