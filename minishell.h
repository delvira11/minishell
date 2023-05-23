/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:32:56 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/23 17:32:11 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct s_counters
{
	int	i;
	int	x;
	int	j;
	int	n;
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
}	t_global;

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

#endif