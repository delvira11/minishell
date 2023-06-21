/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:32:56 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 21:06:42 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_counters
{
	int	i;
	int	x;
	int	j;
	int	n;
	int	k;
}	t_counters;

typedef struct s_norm_expand_var
{
	char		*replace;
	char		*str_return;
}	t_norm_expand_var;

typedef struct s_node
{
	char	*infile;
	char	*delimiter;
	char	*outfile;
	char	*outappend;
	char	*cmd;
}	t_node;

typedef struct s_quotes
{
	char	**linesplitted;
	char	*aux;
	int		i;
}	t_quotes;

typedef struct s_tok_var
{
	char	*aux;
	int		i;
}	t_tok_var;

typedef struct s_fds
{
	int	filein;
	int	fileout;
	int	tub[2];
}	t_fds;

typedef struct s_global
{
	char	**env;
	int		last_cmd_status;
	int		fix_nextfilein;
	int		fix_redir_error;
	char	*exit_code;
	int		cmd_size;
}	t_global;

typedef struct s_pip
{
	int		i;
	int		save;
	int		max_nodes;
}	t_pip;

typedef struct s_path_var
{
	char		*str;
	char		*path;
	char		*path2;
	char		**dir;
	int			i;
	int			x;
}	t_path_var;

typedef struct s_export
{
	char	**var;
	char	**var_name_split;
	char	*varnameigual;
	int		x;
}	t_export;

t_global	g_var;

char		**split_quotes(char *cmd_line);
char		**expand_and_trim(char **linesplitted);
void		parse_function(char *cmd_line);
void		init_global(char **env);
void		free_string_array(char	**strarray);
char		*my_trim(char *s1, char *set);
void		free_string_array(char	**strarray);
t_counters	init_counters(void);
char		*free_and_return(char *str, char *replace, char *str_return);
char		*find_env_var(char	*str);
char		*find_replace(char	*str);
char		*expand_dollar(char *str);
char		*multi_dollar(char	*str);
char		*find_dollar(char *str);
char		**change_pipes(char **linesplitted);
char		*array_to_single_str(char **linesplitted);
char		**split_changed_pipes(char *str);
char		*split_spaces(char *cmd_line, int i);
char		*split_double_quotes(char *cmd_line, int i);
char		*split_simple_quotes(char *cmd_line, int i);
char		**linesplitted_fill(char **linesplitted, char *aux);
t_node		*fill_list(char **linesplitted);
void		exec_pipex(t_node *node);
char		**tokenize_str(char	*str);
int			exec_builtins(char	*cmd);
void		exec_cd(char	*cmd);
char		*get_home_path(void);
char		*cd_back(void);
int			exec_pwd(void);
void		cd_2args(char **cmd);
void		*cd_full_path(char **cmd);
void		cd_folder(char **cmd);
int			exec_builtins_env(char	*cmd);
void		exec_env(void);
void		exec_export(char	*cmd);
void		exec_unset(char	*cmd);
void		exec_echo(char	*cmd);
void		exec_exit(char *cmd);
void		cd_back_noret(void);
char		*ft_strjoin_free(char *s1, char const *s2);
void		free_utils_1(char	**var, char	**var_name_split,
				char *varnameigual);
void		free_utils_2(char	**var_name_split, char	*varnameigual,
				char	**var);
void		exec_env(void);
void		control_c(int n);
void		control_barra(int n);
void		exec_unset(char	*cmd);
void		create_exit_code(void);
void		replace_exit_code(void);
char		**init_env(char	**env);
char		*path(void);
int			norm_quote_error(char	**linesplitted, int x, int i);
int			check_quote_error(char	**linesplitted);
int			norm_redir_errors(char	**t, int i, int x);
int			check_redir_errors(char	**t);
char		*split_spaces(char *cmd_line, int i);
char		*split_double_quotes(char *cmd_line, int i);
char		*split_simple_quotes(char *cmd_line, int i);
char		**linesplitted_fill(char **linesplitted, char *aux);
t_node		norm_infile_1(t_node node, char **linesplitted, int x);
t_node		norm_infile_2(t_node node, char **linesplitted, int x);
t_node		fill_infile(t_node node, char	**linesplitted);
t_node		norm_outfile_1(t_node node, char **linesplitted, int x);
t_node		norm_outfile_2(t_node node, char **linesplitted, int x);
t_node		fill_outfile(t_node node, char	**linesplitted);
t_tok_var	norm_lineeees(char	*str, t_tok_var var);
t_tok_var	norm_tokenize(char	*str, t_tok_var var);
char		**tokenize_str(char	*str);
char		*ft_strjoin_free(char *s1, char const *s2);
char		*split_in_token(char *cmd_line, int i);
char		*split_out_token(char *cmd_line, int i);
char		*split_spaces_new(char *cmd_line, int i);
void		free_tokenized(char	**tokenized);
char		**trim_quotes(char	**tokenized_str);
int			is_builtin(char	*cmd);
int			is_builtin_env(char	*cmd);
char		*free_and_return_line(char	*line);
char		*ft_get_input(char *limit, int fd1, int save);
char		*ft_findpath(char *cmd, char **envp);
void		get_first_infile(t_node *node, int save);
void		norm_filein_error(void);
void		get_next_infile(t_node *node, int i, int tuberia, int save);
void		get_next_stdout(t_node *node, int i, int tuberia);
void		get_last_stdout(t_node *node, int i);
void		free_cmd_splitted(char	**split);
int			exec_builtins(char	*cmd);
int			exec_builtins_env(char	*cmd);
void		cd_back_redir(char **cmd);
void		cd_folder_2(char	*next_path, char	*pwd);
void		cd_folder(char **cmd);
void		exec_cd_free(char **new_cmd, char *home);
void		exec_cd(char *cmd);
void		change_env_var(char	*name, char	*value);
void		cd_2args_2(char	**cmd);
void		cd_2args_free(char	**cmd);
void		cd_2args(char **cmd);
char		*get_home_path(void);
char		*cd_back(void);
t_counters	cd_back_noret_counters(void);
void		cd_back_noret(void);
void		exec_echo(char	*cmd);
int			exec_pwd(void);
int			malloc_size(void);
void		exec_only_export(void);
void		lvl_masuno(char *cmd_line);
void		lvl_masuno_bash(char *cmd_line);
void		shlvl_increase(char *cmd_line);
void		signals(void);
void		norm_export_1(t_export exp);
void		norm_export_2(t_export exp);
void		norm_export(t_export exp);
void		free_cmd_splitted(char	**split);

#endif