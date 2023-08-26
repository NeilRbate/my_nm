CC = clang
CFLAGS = -Wall -Wextra -Werror

NAME = ft_nm

SRCS = src/main.c
LIBFT = -L. libft/libft.a 

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@make -C libft all
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}


clean:
	@rm -f ${OBJS}
	@make -C libft clean

fclean: clean
	@rm -f ${NAME}
	@make -C libft clean

re: fclean all

.PHONY: all clean fclean re
