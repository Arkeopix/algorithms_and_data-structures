NAME	=	linked_list
CC		=	gcc
SRC		=	linked_list.c
OBJ		=	${SRC:.c=.o}
CFLAGS	=	-ansi		\
			-pedantic	\
			-Wall		\
			-Wextra		\
			-std=c11

${NAME}:	${OBJ}
			${CC} -g ${OBJ} -o ${NAME} ${CFLAGS}

all:		${NAME}

clean:
			rm -vf ${OBJ}

fclean:		clean
			rm -vf ${NAME}

re:			fclean all
