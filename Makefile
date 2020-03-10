##
## EPITECH PROJECT, 2020
## Alexandre Wagner
## File description:
## make strace
##

D_SRC		=	./src/
D_INC		=	./include/

NAME		=	strace

SRC			=	$(D_SRC)print_ft.c \
				$(D_SRC)main.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Wextra -I$(D_INC)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean	:
			rm -f $(OBJ)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
