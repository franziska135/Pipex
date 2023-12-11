NAME	=	pipex
INC		=	pipex.h
CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
AR		=	ar rc
RM		=	rm -f

SRC		=	pipex.c cleanup.c libft.c envp.c setup.c children.c utils.c \
			libft2.c

OBJ		=	$(SRC:.c=.o)

.PHONY:		all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) -o $(NAME)

%.o: %.c	$(INC)
			$(CC) -c $< -o $@
#			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			clean all