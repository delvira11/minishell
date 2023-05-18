/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_pipe_to_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:02:02 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/18 16:59:37 by delvira-         ###   ########.fr       */
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


t_node	fill_infile(t_node node, char	**linesplitted)
{
	int	x;

	x = 0;
	node.infile = NULL;
	node.delimiter = NULL;
	while (linesplitted[x])
	{
		if (linesplitted[x][0] == '<')
		{
			if (linesplitted[x][1] != '<')
			{
				node.infile = linesplitted[x + 1];
				if (node.delimiter != NULL)
					node.delimiter = NULL;
				x++;
			}
			else if (linesplitted[x][1] == '<')
			{
				node.delimiter = linesplitted[x + 1];
				if (node.infile != NULL)
					node.infile = NULL;
				x++;
			}
		}
		x++;
	}
	return (node);
}

t_node	fill_outfile(t_node node, char	**linesplitted)
{
	int	x;

	x = 0;
	node.outfile = NULL;
	node.outappend = NULL;
	while (linesplitted[x])
	{
		if (linesplitted[x][0] == '>')
		{
			if (linesplitted[x][1] != '>')
			{
				node.outfile = linesplitted[x + 1];
				if (node.outappend != NULL)
					node.outappend = NULL;
				x++;
			}
			else if (linesplitted[x][1] == '>')
			{
				node.outappend = linesplitted[x + 1];
				if (node.outfile != NULL)
					node.outfile = NULL;
				x++;
			}
		}
		x++;
	}
	return (node);
}

t_node	fill_cmd(t_node node, char **linesplitted)
{
	int		x;
	char	*str;

	x = 0;
	str = "";
	node.cmd = NULL;
	while (linesplitted[x])
	{
		if (linesplitted[x][0] == '<' || linesplitted[x][0] == '>')
		{
			x += 1;
		}
		else
		{
			str = ft_strjoin(str, linesplitted[x]);
			str = ft_strjoin(str, " ");
		}
		x++;
	}
	node.cmd = str;
	return (node);
}

t_node	fill_node(char	*str)
{
	t_node	node;
	char	**tokenized_str;

	tokenized_str = tokenize_str(str);
	node = fill_infile(node, tokenized_str);
	node = fill_outfile(node, tokenized_str);
	node = fill_cmd(node, tokenized_str);
	return (node);
	// printf("infile: %s\n", node.infile);
	// printf("delimiter: %s\n", node.delimiter);
	// printf("cmd: %s\n", node.cmd);
	// printf("outfile: %s\n", node.outfile);
	// printf("outappend: %s\n", node.outappend);
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
