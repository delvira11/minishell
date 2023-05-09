/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_trim_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:04:59 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/09 17:29:43 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////NO TRIMEAR PORQUE PUEDE HABER UN PIPE ENTRE COMILLAS Y LUEGO NO PODREMOS HACER SPLIT POR PIPES////

char	**expand_and_trim(char **linesplitted)
{
	int	x;

	x = 0;
	while (linesplitted[x])
	{
		if (linesplitted[x][0] != '\'')
		{
			linesplitted[x] = find_dollar(linesplitted[x]);
		}
		x++;
	}
	x = 0;
	// while (linesplitted[x])
	// {
	// 	if (linesplitted[x][0] == '\"')
	// 	{
	// 		linesplitted[x] = my_trim(linesplitted[x], "\"");
	// 	}
	// 	else if (linesplitted[x][0] == '\'')
	// 		linesplitted[x] = my_trim(linesplitted[x], "\'");
	// 	x++;
	// }
	return (linesplitted);
}
