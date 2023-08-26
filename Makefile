GCC = gcc
SRCS = /src/main.c
HEADER = 
OBJS = ${SRCS:.c=.o}
NAME = ft_nm
CFLAGS = -Wall -Wextra -Werror

.c.o:
	${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${GCC} ${CFLAGS} -o ${NAME} ${OBJS}

all: ${NAME}

clean:
	@rm -f ${OBJS}
	@echo Everything is clean

fclean:
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
