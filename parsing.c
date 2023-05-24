/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:20:20 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/24 17:56:03 by delvira-         ###   ########.fr       */
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

int	check_quote_error(char	**linesplitted)
{
	int	x;
	int	i;

	x = 0;
	while (linesplitted[x])
	{
		i = 0;
		if (linesplitted[x][0] == '\"')
		{
			while (linesplitted[x][i] != '\0')
				i++;
			if (linesplitted[x][i - 1] != '\"' || (i - 1) == 0)
			{
				free_string_array(linesplitted);
				write(1, "quote error", 12);
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
				write(1, "quote error", 12);
				return (-1);
			}
		}
		x++;
	}
	return (0);
}

int	check_redir_errors(char	**tokenized_str)
{
	int	x;
	int	i;

	x = 0;
	while (tokenized_str[x])
	{
		i = 0;
		if (tokenized_str[x][0] != '\'' && tokenized_str[x][0] != '\"')
		{
			while (tokenized_str[i])
			{
				if (tokenized_str[x][i] == '<')
				{
					if (tokenized_str[x][i + 1] == '<' && tokenized_str[x][i + 2] == '<')
						return (-1);
					else if (tokenized_str[x][i + 1] == '<' && tokenized_str[x][i + 2] == '>')
						return (-1);
					else if (tokenized_str[x][i + 1] == '>')
						return (-1);
				}
				else if (tokenized_str[x][i] == '>')
				{
					if (tokenized_str[x][i + 1] == '>' && tokenized_str[x][i + 2] == '>')
						return (-1);
					else if (tokenized_str[x][i + 1] == '>' && tokenized_str[x][i + 2] == '<')
						return (-1);
					else if (tokenized_str[x][i + 1] == '<')
						return (-1);
				}
				i++;
			}
		}
		x++;
	}
	return (0);
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
		printf("\nredir error\n");
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
