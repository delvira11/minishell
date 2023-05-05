/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:24:31 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/05 18:21:57 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_spaces(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(1000, sizeof(char));
	j = 0;
	while (cmd_line[i] != ' ' && cmd_line[i] != '"' && cmd_line[i] != '\'' && cmd_line[i] != '\0')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	// printf("%s", aux);
	return (aux);
}

char	*split_double_quotes(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(1000, sizeof(char));
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
	// printf("%s", aux);
	return (aux);
}

char	*split_simple_quotes(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(1000, sizeof(char));
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
	// printf("%s", aux);
	return (aux);
}

char	**linesplitted_fill(char **linesplitted, char *aux)
{
	int x;

	x = 0;
	while (linesplitted[x])
		x++;
	linesplitted[x] = aux;
	return (linesplitted);
}

char	**split_quotes(char *cmd_line)
{
	char	**linesplitted;
	char	*aux;
	int		i;

	i = 0;
	linesplitted = ft_calloc(1000, sizeof(char *));
	while (cmd_line[i] != '\0')
	{
		while (cmd_line[i] == ' ')
			i++;
		if (cmd_line[i] == '\"')
		{
			aux = split_double_quotes(cmd_line, i);
			i += ft_strlen(aux) + 1;
		}
		else if (cmd_line[i] == '\'')
		{
			aux = split_simple_quotes(cmd_line, i);
			i += ft_strlen(aux) + 1;
		}
		else
		{
			aux = split_spaces(cmd_line, i);
			i += ft_strlen(aux);
		}
		linesplitted = linesplitted_fill(linesplitted, aux);
	}
	return (linesplitted);
}
