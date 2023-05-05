CC= gcc -g
NAME=minishell
LIBFTA=libft/libft.a
CFLAGS= -Wall -Wextra -Werror
LIBRARIES= -lreadline
SRC= main.c split_quotes.c
OBJ=$(SRC:.c=.o)


all: libft $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTA) -o $(NAME) $(LIBRARIES)

libft:
	make -C ./libft all

clean:
	rm -rf $(OBJ)
	make -C libft clean

fclean:
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: libft