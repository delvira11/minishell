/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:32:56 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/08 18:02:03 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct s_global
{
	char	**env;
	int		dollarcount;

}	t_global;

t_global	g_var;

char	**split_quotes(char *cmd_line);
char	**expand_variables(char **linesplitted);
void	parse_function(char *cmd_line);
void	init_global(char **env);

#endif