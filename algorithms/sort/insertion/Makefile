SRC 	= main.c
OBJ 	= ${SRC:.c=.o}
NAME 	= insertion_sort
CFLAGS 	= -std=c99 -pedantic -Wall -Werror -Wextra -Wunused
${NAME}:  	${OBJ}
		  	${CC} ${OBJ} ${CFLAGS} -o ${NAME}
all:      	${NAME}
clean:
			${RM} ${OBJ}
fclean:   	clean
			${RM} ${NAME}
re:       	fclean all
