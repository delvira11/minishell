/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:05:49 by ide-albe          #+#    #+#             */
/*   Updated: 2023/05/10 15:05:53 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**change_pipes(char **linesplitted)
{
	int	i;
	int	j;

	i = 0;
	while (linesplitted[i])
	{
		j = 0;
		while (linesplitted[i][j] != '\0')
		{
			if (linesplitted[i][0] == '\"' || linesplitted[i][0] == '\'')
				break ;
			if (linesplitted[i][j] == '|')
				linesplitted[i][j] = '*';
			j++;
		}
		i++;
	}
	return (linesplitted);
}

char	*array_to_single_str(char **linesplitted)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	str = ft_calloc(1000, sizeof(char));
	while (linesplitted[i])
	{
		j = 0;
		while (linesplitted[i][j] != '\0')
		{
			str[k] = linesplitted[i][j];
			k++;
			j++;
		}
		str[k] = ' ';
		k++;
		i++;
	}
	return (str);
}

char	**split_changed_pipes(char *str)
{
	char	**linesplitted;

	linesplitted = ft_split(str, '*');
	return (linesplitted);
}
