SRC		=	main.c
OBJ		=	${SRC:.c=.o}
NAME	=	vigenere
CC		=	gcc
CFLAGS	=	-ansi 		\
			-pedantic	\
			-Wall		\
			-Wextra		
${NAME}:	${OBJ}
			${CC} ${OBJ} ${CFLAGS} -o ${NAME}

all:		${NAME}

clean:
			rm -vf ${OBJ}

fclean:		clean
			rm -vf ${NAME}

re:			fclean all
