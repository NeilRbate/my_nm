CC = clang
CFLAGS = -Wall -Wextra -Werror

NAME = ft_nm

SRCS = src/main.c
HEADER = include/include.h 

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}


clean:
	@rm -f ${OBJS}
	@echo Everything is clean

fclean:
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
