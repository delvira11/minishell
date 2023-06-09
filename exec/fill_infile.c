/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:36:22 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 18:59:11 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	norm_infile_1(t_node node, char **linesplitted, int x)
{
	if (node.infile != NULL)
		free(node.infile);
	node.infile = linesplitted[x + 1];
	if (node.delimiter != NULL)
	{
		free (node.delimiter);
		node.delimiter = NULL;
	}
	return (node);
}

t_node	norm_infile_2(t_node node, char **linesplitted, int x)
{
	if (node.delimiter != NULL)
		free(node.delimiter);
	node.delimiter = linesplitted[x + 1];
	if (node.infile != NULL)
	{
		free (node.infile);
		node.infile = NULL;
	}
	return (node);
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
				node = norm_infile_1(node, linesplitted, x);
				x++;
			}
			else if (linesplitted[x][1] == '<')
			{
				node = norm_infile_2(node, linesplitted, x);
				x++;
			}
		}
		x++;
	}
	return (node);
}
