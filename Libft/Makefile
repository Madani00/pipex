NAME = libft.a
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_split.c ft_strdup.c ft_strlen.c ft_putstr_fd.c \
		ft_strchr.c ft_strjoin.c ft_strncmp.c ft_substr.c

all: ${NAME}

OBJS = ${SRCS:%.c=%.o}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

%.o:%.c
		${CC} ${FLAGS} -c $< -o $@

clean:
		${RM} ${OBJS} ${BONUS_OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: clean fclean re all bonus

.SECONDARY:

