NAME	=	otp
SRC		=	main.c
OBJ		=	${SRC:.c=.o}
CC		=	gcc
CFLAGS	=	-Wall		\
			-Wextra		\
			-Werror		\
			-pedantic	\
			-ansi

name:		${OBJ}
			${CC} -g ${OBJ} ${CFLAGS} -o ${NAME}

all:		${NAME}

clean:
			rm -vf ${OBJ}

fclean:		clean
			rm -vf ${NAME}

re:			fclean all
