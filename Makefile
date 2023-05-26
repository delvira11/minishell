CC= gcc -g
NAME=minishell
LIBFTA=libft/libft.a
CFLAGS= -Wall -Wextra -Werror
LIBRARIES= -lreadline
SRC= main.c split_quotes.c parsing.c expand_and_trim_1.c expand_and_trim_2.c expand_and_trim_utils.c main_utils.c change_pipes.c exec.c \
	from_pipe_to_node.c exit.c export.c export_utils.c env.c signals.c unset.c exit_code.c quote_and_redir_errors.c split_quotes_utils.c \
	fill_infile.c fill_outfile.c tokenize_str.c tokenize_str_utils.c tokenize_str_utils_2.c is_builtin_func.c exec_utils_1.c exec_fd_manage.c \
	cd.c cd_2.c cd_3.c echo.c pwd.c
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