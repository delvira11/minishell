CC= gcc -g
NAME=minishell
LIBFTA=libft/libft.a
CFLAGS= -Wall -Wextra -Werror
LIBRARIES= -lreadline
SRC= main.c parse/split_quotes.c parse/parsing.c parse/expand_and_trim_1.c parse/expand_and_trim_2.c parse/expand_and_trim_utils.c utils/main_utils.c parse/change_pipes.c exec/exec.c \
	parse/from_pipe_to_node.c builtins/exit.c builtins/export.c builtins/export_utils.c builtins/env.c utils/signals.c builtins/unset.c exec/exit_code.c parse/quote_and_redir_errors.c parse/split_quotes_utils.c \
	exec/fill_infile.c exec/fill_outfile.c parse/tokenize_str.c parse/tokenize_str_utils.c parse/tokenize_str_utils_2.c builtins/is_builtin_func.c exec/exec_utils_1.c exec/exec_fd_manage.c \
	builtins/cd.c builtins/cd_2.c builtins/cd_3.c builtins/echo.c builtins/pwd.c
OBJ=$(SRC:.c=.o)


all: libft $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFTA) -o $(NAME) $(LIBRARIES)

libft:
	make -C ./libft all

clean:
	rm -rf $(OBJ)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: libft