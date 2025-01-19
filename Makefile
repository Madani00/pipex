NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MK = make

SRCS = main.c ft_free.c pipex_utils.c

# S_BONUS = operation2_bonus.c operations_bonus.c get_next_line_bonus.c \
# 		main_bonus.c frees_bonus.c pushswap_utils_bonus.c \


OBJS = $(SRCS:.c=.o)

# OBJS_BONUS = $(S_BONUS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		$(MK) -C ./Libft
		$(CC) $(CFLAGS) $(OBJS) ./Libft/libft.a -o $(NAME)

clean:
		$(MK) clean -C ./Libft
		${RM} ${OBJS} $(OBJS_BONUS)

fclean: clean
		$(MK) fclean -C ./Libft
		$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY:
