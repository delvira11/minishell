/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_pipe_to_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:02:02 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/19 22:33:38 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;
	size_t	i;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = (char *)ft_calloc((s1len + s2len + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1len + 1);
	i = 0;
	while (i < s2len)
	{
		str[s1len + i] = s2[i];
		i++;
	}
	// if (s1[0] != '\0')
	free(s1);
	return (str);
}

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
				if (node.infile != NULL)
					free(node.infile);
				node.infile = linesplitted[x + 1];
				if (node.delimiter != NULL)
				{
					free (node.delimiter);
					node.delimiter = NULL;
				}
				x++;
			}
			else if (linesplitted[x][1] == '<')
			{
				if (node.delimiter != NULL)
					free(node.delimiter);
				node.delimiter = linesplitted[x + 1];
				if (node.infile != NULL)
				{
					free (node.infile);
					node.infile = NULL;
				}
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
				if (node.outfile != NULL)
					free(node.outfile);
				node.outfile = linesplitted[x + 1];
				if (node.outappend != NULL)
				{
					free (node.outappend);
					node.outappend = NULL;
				}
				x++;
			}
			else if (linesplitted[x][1] == '>')
			{
				if (node.outappend != NULL)
					free(node.outappend);
				node.outappend = linesplitted[x + 1];
				if (node.outfile != NULL)
				{
					free (node.outfile);
					node.outfile = NULL;
				}
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
	str = ft_calloc(1000, sizeof(char));
	node.cmd = NULL;
	while (linesplitted[x])
	{
		if (linesplitted[x][0] == '<' || linesplitted[x][0] == '>')
		{
			x += 1;
		}
		else
		{
			str = ft_strjoin_free(str, linesplitted[x]);
			free(linesplitted[x]);
			str = ft_strjoin_free(str, " ");
		}
		x++;
	}
	node.cmd = str;
	return (node);
}

void free_tokenized(char	**tokenized)
{
	int	x;

	x = 0;
	while (tokenized[x])
	{
		if ((tokenized[x][0] == '<') || tokenized[x][0] == '>')
			free(tokenized[x]);
		x++;
	}
}

t_node	fill_node(char	*str)
{
	t_node	node;
	char	**tokenized_str;

	tokenized_str = tokenize_str(str);
	node = fill_infile(node, tokenized_str);
	node = fill_outfile(node, tokenized_str);
	node = fill_cmd(node, tokenized_str);
	free_tokenized(tokenized_str);
	free(tokenized_str);
	return (node);
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
