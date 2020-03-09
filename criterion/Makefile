##
## EPITECH PROJECT, 2020
## Alexandre Wagner - Théo Le bonniec
## File description:
## Makefile test_criterion
##

D_SRC	=	./src/

SRC		=	$(D_SRC)main.c

OBJ		=	$(SRC:.c=.o)

LDFLAGS	=	-lcriterion --coverage
CFLAGS	+=	-W -Wall -Wextra

NAME	=	unit_test

all	:	$(NAME)

$(NAME):	$(OBJ)
			gcc -o $(NAME) $(OBJ) $(LDFLAGS)
			./$(NAME)

clean	:
			rm -rf $(OBJ)

fclean	:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re