NAME = pwm

SRC = ${wildcard src/*.c}

OBJ = ${SRC:.c=.o}

LIB = lib/libny.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

DEFINES = -D BASE_DIR='"/home/${USER}/.pwm/"'

RM = rm -rf

.c.o:
	${CC} ${CFLAGS} ${DEFINES} -Iinc -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	${CC} -o ${NAME} ${OBJ} ${LIB}
	mv ${NAME} /home/${USER}/.local/bin/
	mkdir -p /home/${USER}/.pwm/backups/

all: ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}
	${RM} /home/${USER}/.local/bin/${NAME}
	${RM} /home/${USER}/.pwm/

re: fclean all

.PHONY: all clean fclean re
