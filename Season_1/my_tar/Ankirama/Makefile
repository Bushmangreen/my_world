CC	= gcc

RM	= rm -f

CFLAGS	+= -ansi -pedantic

CFLAGS	+= -D_BSD_SOURCE

SRCS	= my_tar.c \
	  my_untar.c \
	  main.c \
	  my_create.c \
	  my_dir.c \
	  my_options.c \
	  my_append.c \
	  my_append_nbr.c \
	  my_file.c \
	  my_nbr.c \
	  my_fun.c

NAME	= my_tar

OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re