SRC=	main.c
OBJ=	${SRC:.c=.o}
NAME=	merge_sort
CFLAGS=	-std=c99 -pedantic -Wextra -W -Werror -Wunused
${NAME}:	${OBJ}
			${CC} ${OBJ} ${CFLAGS} -o ${NAME}
all:		${NAME}
clean:
			${RM} ${OBJ}
fclean:		clean
			${RM} ${NAME}
re:			fclean all
