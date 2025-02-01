NAME = pipex
BONUS_NAME = bpipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MK = make

SRCS = main.c ft_free_error.c pipex_utils.c checking.c

S_BONUS = main_bonus.c get_next_line.c bonus_utils.c bonus_utils2.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(S_BONUS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		$(MK) -C ./Libft
		$(CC) $(CFLAGS) $(OBJS) ./Libft/libft.a -o $(NAME)

bonus : $(BONUS_NAME)

$(BONUS_NAME) : $(OBJS_BONUS) ./Libft/libft.a
		$(CC) $(CFLAGS) $(OBJS_BONUS) ./Libft/libft.a -o $(BONUS_NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

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
