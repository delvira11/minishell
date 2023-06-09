/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:07:20 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/09 15:49:33 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_spaces(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(malloc_size(), sizeof(char));
	j = 0;
	while (cmd_line[i] != ' ' && cmd_line[i] != '"'
		&& cmd_line[i] != '\'' && cmd_line[i] != '\0')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	return (aux);
}

char	*split_double_quotes(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(malloc_size(), sizeof(char));
	j = 1;
	i++;
	aux[0] = '\"';
	while (cmd_line[i] != '\"')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	aux[j] = '\"';
	return (aux);
}

char	*split_simple_quotes(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(malloc_size(), sizeof(char));
	j = 1;
	i++;
	aux[0] = '\'';
	while (cmd_line[i] != '\'')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	aux[j] = '\'';
	return (aux);
}

char	**linesplitted_fill(char **linesplitted, char *aux)
{
	int	x;

	x = 0;
	while (linesplitted[x])
		x++;
	linesplitted[x] = aux;
	return (linesplitted);
}
