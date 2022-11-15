NAME = password_manager

SRC = ${wildcard src/*.c}

OBJ = ${SRC:.c=.o}

LIB = lib/libny.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

.c.o:
	${CC} ${CFLAGS} -Iinc -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	${CC} -o ${NAME} ${OBJ} ${LIB}

all: ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
