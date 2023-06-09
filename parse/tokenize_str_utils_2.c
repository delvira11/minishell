/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_str_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:42:39 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 19:00:07 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokenized(char	**tokenized)
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

char	**trim_quotes(char	**tokenized_str)
{
	int	x;

	x = 0;
	while (tokenized_str[x])
	{
		if (tokenized_str[x][0] == '\"')
		{
			tokenized_str[x] = my_trim(tokenized_str[x], "\"");
		}
		else if (tokenized_str[x][0] == '\'')
		{
			tokenized_str[x] = my_trim(tokenized_str[x], "\'");
		}
		x++;
	}
	return (tokenized_str);
}
