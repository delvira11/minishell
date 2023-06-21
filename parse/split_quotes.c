/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:24:31 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 17:12:18 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotes	norm_init_var_quotes(void)
{
	t_quotes	q_var;

	q_var.i = 0;
	q_var.linesplitted = ft_calloc(malloc_size(), sizeof(char *));
	return (q_var);
}

char	**split_quotes(char *cmd_line)
{
	t_quotes	q_var;

	q_var = norm_init_var_quotes();
	while (cmd_line[q_var.i] != '\0')
	{
		while (cmd_line[q_var.i] == ' ')
			q_var.i++;
		if (cmd_line[q_var.i] == '\"')
		{
			q_var.aux = split_double_quotes(cmd_line, q_var.i);
			q_var.i += ft_strlen(q_var.aux);
		}
		else if (cmd_line[q_var.i] == '\'')
		{
			q_var.aux = split_simple_quotes(cmd_line, q_var.i);
			q_var.i += ft_strlen(q_var.aux);
		}
		else
		{
			q_var.aux = split_spaces(cmd_line, q_var.i);
			q_var.i += ft_strlen(q_var.aux);
		}
		q_var.linesplitted = linesplitted_fill(q_var.linesplitted, q_var.aux);
	}
	return (q_var.linesplitted);
}
