##
## EPITECH PROJECT, 2020
## Alexandre Wagner
## File description:
## make strace
##

D_SRC		=	./src/
D_INC		=	./include/
D_TEST		=	./criterion/

NAME		=	strace

SRC			=	$(D_SRC)main.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Wextra -I$(D_INC)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean	:
			rm -f $(OBJ)

fclean	:	clean
			rm -f $(NAME)
			make fclean -C $(D_TEST)

re		:	fclean all

tests_run	:
				make re -C $(D_TEST)

.PHONY	:	all clean fclean re
