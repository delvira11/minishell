/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_redir_errors.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:58:28 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 17:26:14 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	norm_quote_error(char	**linesplitted, int x, int i)
{
	if (linesplitted[x][0] == '\"')
	{
		while (linesplitted[x][i] != '\0')
			i++;
		if (linesplitted[x][i - 1] != '\"' || (i - 1) == 0)
		{
			free_string_array(linesplitted);
			write(1, "quote error\n", 13);
			return (-1);
		}
	}
	else if (linesplitted[x][0] == '\'')
	{
		while (linesplitted[x][i] != '\0')
			i++;
		if (linesplitted[x][i - 1] != '\'' || (i - 1) == 0)
		{
			free_string_array(linesplitted);
			write(1, "quote error\n", 13);
			return (-1);
		}
	}
	return (0);
}

int	check_quote_error(char	**linesplitted)
{
	int	x;
	int	i;

	x = 0;
	while (linesplitted[x])
	{
		i = 0;
		if (norm_quote_error(linesplitted, x, i) == -1)
			return (-1);
		x++;
	}
	return (0);
}

int	norm_redir_errors(char	**t, int i, int x)
{
	if (t[x][i] == '<')
	{
		if (t[x][i + 1] == '<' && t[x][i + 2] == '<')
			return (-1);
		else if (t[x][i + 1] == '<' && t[x][i + 2] == '>')
			return (-1);
		else if (t[x][i + 1] == '>')
			return (-1);
	}
	else if (t[x][i] == '>')
	{
		if (t[x][i + 1] == '>' && t[x][i + 2] == '>')
			return (-1);
		else if (t[x][i + 1] == '>' && t[x][i + 2] == '<')
			return (-1);
		else if (t[x][i + 1] == '<')
			return (-1);
	}
	return (0);
}

int	check_redir_errors(char	**t)
{
	int	x;
	int	i;

	x = 0;
	while (t[x])
	{
		i = 0;
		if (t[x][0] != '\'' && t[x][0] != '\"')
		{
			while (t[i])
			{
				if (norm_redir_errors(t, i, x) == -1)
					return (-1);
				i++;
			}
		}
		x++;
	}
	return (0);
}
