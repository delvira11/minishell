/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:40:03 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 18:59:36 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok_var	norm_lineeees(char	*str, t_tok_var var)
{
	var.aux = split_double_quotes(str, var.i);
	var.i += ft_strlen(var.aux);
	return (var);
}

t_tok_var	norm_tokenize(char	*str, t_tok_var var)
{
	if (str[var.i] == '\"')
	{
		var = norm_lineeees(str, var);
	}
	else if (str[var.i] == '\'')
	{
		var.aux = split_simple_quotes(str, var.i);
		var.i += ft_strlen(var.aux);
	}
	else if (str[var.i] == '<')
	{
		var.aux = split_in_token(str, var.i);
		var.i += ft_strlen(var.aux);
	}
	else if (str[var.i] == '>')
	{
		var.aux = split_out_token(str, var.i);
		var.i += ft_strlen(var.aux);
	}
	else
	{
		var.aux = split_spaces_new(str, var.i);
		var.i += ft_strlen(var.aux);
	}
	return (var);
}

char	**tokenize_str(char	*str)
{
	char		**linesplitted;
	t_tok_var	var;

	var.i = 0;
	linesplitted = ft_calloc(1000, sizeof(char *));
	while (str[var.i] != '\0')
	{
		while (str[var.i] == ' ')
			var.i++;
		var = norm_tokenize(str, var);
		linesplitted = linesplitted_fill(linesplitted, var.aux);
	}
	return (linesplitted);
}
