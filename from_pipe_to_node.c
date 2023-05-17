/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_pipe_to_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:02:02 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/17 19:07:57 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_in_token(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(1000, sizeof(char));
	j = 0;
	while (cmd_line[i] == '<')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	return (aux);
}

char	*split_out_token(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(1000, sizeof(char));
	j = 0;
	while (cmd_line[i] == '>')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	return (aux);
}

char	*split_spaces_new(char *cmd_line, int i)
{
	char	*aux;
	int		j;

	aux = ft_calloc(1000, sizeof(char));
	j = 0;
	while (cmd_line[i] != ' ' && cmd_line[i] != '"'
		&& cmd_line[i] != '\'' && cmd_line[i] != '\0'
		&& cmd_line[i] != '<' && cmd_line[i] != '>')
	{
		aux[j] = cmd_line[i];
		i++;
		j++;
	}
	return (aux);
}

char	**tokenize_str(char	*str)
{
	char	**linesplitted;
	char	*aux;
	int		i;

	i = 0;
	linesplitted = ft_calloc(1000, sizeof(char *));
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\"')
		{
			aux = split_double_quotes(str, i);
			i += ft_strlen(aux);
		}
		else if (str[i] == '\'')
		{
			aux = split_simple_quotes(str, i);
			i += ft_strlen(aux);
		}
		else if (str[i] == '<')
		{
			aux = split_in_token(str, i);
			i += ft_strlen(aux);
		}
		else if (str[i] == '>')
		{
			aux = split_out_token(str, i);
			i += ft_strlen(aux);
		}
		else
		{
			aux = split_spaces_new(str, i);
			i += ft_strlen(aux);
		}
		linesplitted = linesplitted_fill(linesplitted, aux);
	}
	return (linesplitted);
}

t_node	fill_node(char	*str)
{
	t_node	node;
	char	**tokenized_str;

	tokenized_str = tokenize_str(str);



}

t_node	*fill_list(char **linesplitted)
{
	t_node	*node;
	int		x;

	x = 0;
	node = ft_calloc(50, sizeof(t_node));
	while (linesplitted[x])
	{
		node[x] = fill_node(linesplitted[x]);
		x++;
	}
	return (node);
}
