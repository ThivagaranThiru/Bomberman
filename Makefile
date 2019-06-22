##
## ETNA PROJECT, 17/05/2019 by lao_q
## [...]
## File description:
##      [...]
##

CC =		gcc

NAME =		bomberman

SRC =		window.c \
			game.c \
			input.c \
			player.c \
			map.c \
			bomb.c \
			Server.c \
			Client.c \
			main.c

OBJS	=	$(SRC:.c=.o)

CFLAGS	= -pthread -lSDL2 -lSDL2_image -lSDL2_ttf -lX11

RM	=	rm -f

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean re