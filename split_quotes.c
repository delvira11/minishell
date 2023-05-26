/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:24:31 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 17:07:55 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quotes	norm_init_var_quotes(void)
{
	t_quotes	q_var;

	q_var.i = 0;
	q_var.linesplitted = ft_calloc(1000, sizeof(char *));
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
