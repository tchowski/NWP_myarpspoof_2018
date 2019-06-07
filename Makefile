CC	=	gcc -g3

RM	=	rm -f

SRC	=	get_mac_adrresses.c	\
		main.c				\
		run.c				\
		set_structur.c		\
		utils.c				\
		print.c

DIR_SRC = src

OBJ	=	$(addprefix $(DIR_SRC)/, $(SRC:.c=.o))

CFLAGS	=	-Iincludes -Wall -Wextra

NAME	=	my_arpspoof

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re