/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:38:15 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 18:38:51 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	norm_outfile_1(t_node node, char **linesplitted, int x)
{
	if (node.outfile != NULL)
		free(node.outfile);
	node.outfile = linesplitted[x + 1];
	if (node.outappend != NULL)
	{
		free (node.outappend);
		node.outappend = NULL;
	}
	return (node);
}

t_node	norm_outfile_2(t_node node, char **linesplitted, int x)
{
	if (node.outappend != NULL)
		free(node.outappend);
	node.outappend = linesplitted[x + 1];
	if (node.outfile != NULL)
	{
		free (node.outfile);
		node.outfile = NULL;
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
				node = norm_outfile_1(node, linesplitted, x);
				x++;
			}
			else if (linesplitted[x][1] == '>')
			{
				node = norm_outfile_2(node, linesplitted, x);
				x++;
			}
		}
		x++;
	}
	return (node);
}
