CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

NAME = ft_nm

SRCS = src/main.c \
       src/init.c \
       src/parser.c \
       src/tools.c \
       src/elfcompute.c \
       src/elf32compute.c \
       src/elf64compute.c

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
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
