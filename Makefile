NAME	=	pipex
NAME2	=	pipex_bonus
INC		= 	pipex.h
CC		=	cc
CFLAGS	=	-g
# CFLAGS	=	-Wall -Wextra -Werror -g
AR		=	ar rc
RM		=	rm -f

SRC		=	children.c cleanup.c envp.c libft2.c libft.c\
			pipex.c setup.c	utils.c

SRC2	=	pipex_bonus.c cleanup.c envp.c libft2.c libft.c\
			setup.c	utils.c pipex.c

OBJS	=	$(SRC:.c=.o)
OBJS2	=	$(SRC2:.c=.o)

.PHONY:		all clean fclean re

all:		$(NAME)

all2:		$(NAME2)

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

$(NAME2):	$(OBJS2)
			$(CC) $(OBJS2) -o $(NAME2)

%.o: %.c 	$(INC)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJS) $(OBJS2)

fclean: 	clean
			$(RM) $(NAME) $(NAME2)

re:			clean all

bonus:		clean all2
