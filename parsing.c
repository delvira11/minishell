/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:20:20 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/08 21:46:45 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////////////////////PROBAR CON BASH TODOOOOOOOOO////////////////////

void    parse_function(char *cmd_line)
{
    char    **linesplitted;

	linesplitted = split_quotes(cmd_line);
    linesplitted = expand_variables(linesplitted);
	int x = 0;
	while (linesplitted[x] != NULL)
	{
		printf("%s\n", linesplitted[x]);
		x++;
	}
}
