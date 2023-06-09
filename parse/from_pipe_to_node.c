/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_pipe_to_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:02:02 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/09 15:47:39 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	fill_cmd(t_node node, char **linesplitted)
{
	int		x;
	char	*str;

	free(node.cmd);
	x = 0;
	str = ft_calloc(malloc_size(), sizeof(char));
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

t_node	fill_node(char	*str)
{
	t_node	node;
	char	**tokenized_str;

	node.cmd = ft_calloc(malloc_size(), sizeof(char));
	tokenized_str = tokenize_str(str);
	tokenized_str = trim_quotes(tokenized_str);
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
	node = ft_calloc(malloc_size(), sizeof(t_node));
	while (linesplitted[x])
	{
		node[x] = fill_node(linesplitted[x]);
		x++;
	}
	return (node);
}
