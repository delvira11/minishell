/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:20:20 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 17:11:23 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nodes(t_node *node)
{
	int	x;

	x = 0;
	while (node[x].cmd)
	{
		if (node[x].cmd)
			free(node[x].cmd);
		if (node[x].infile)
			free(node[x].infile);
		if (node[x].delimiter)
			free(node[x].delimiter);
		if (node[x].outfile)
			free(node[x].outfile);
		if (node[x].outappend)
			free(node[x].outappend);
		x++;
	}
	free(node);
}

void	parse_function(char *cmd_line)
{
	char	**linesplitted;
	char	*single_str;
	t_node	*node;

	linesplitted = split_quotes(cmd_line);
	if (check_quote_error(linesplitted) < 0)
		return ;
	if (check_redir_errors(linesplitted) < 0)
	{
		printf("redir error\n");
		free_string_array(linesplitted);
		return ;
	}
	linesplitted = expand_and_trim(linesplitted);
	linesplitted = change_pipes(linesplitted);
	single_str = array_to_single_str(linesplitted);
	free_string_array(linesplitted);
	linesplitted = split_changed_pipes(single_str);
	node = fill_list(linesplitted);
	exec_pipex(node);
	free_string_array(linesplitted);
	free(single_str);
	free_nodes(node);
}
