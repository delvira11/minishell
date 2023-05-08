/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:24:31 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/08 21:34:07 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_spaces(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(1000, sizeof(char));
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
			i += ft_strlen(aux);
		}
		else if (cmd_line[i] == '\'')
		{
			aux = split_simple_quotes(cmd_line, i);
			i += ft_strlen(aux);
		}
		else
		{
			aux = split_spaces(cmd_line, i);
			i += ft_strlen(aux);
		}
		linesplitted = linesplitted_fill(linesplitted, aux);
	}
	// int x = 0;
	// while (linesplitted[x])
	// {
	// 	printf("\n%s\n", linesplitted[x]);
	// 	x++;
	// }
	return (linesplitted);
}
