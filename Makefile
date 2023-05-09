CC= gcc -g
NAME=minishell
LIBFTA=libft/libft.a
CFLAGS= -Wall -Wextra
LIBRARIES= -lreadline
SRC= main.c split_quotes.c parsing.c expand_and_trim_1.c expand_and_trim_2.c expand_and_trim_utils.c main_utils.c
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