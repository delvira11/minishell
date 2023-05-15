/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:20:20 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/11 17:21:39 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////////////////////PROBAR CON BASH TODOOOOOOOOO////////////////////

void    parse_function(char *cmd_line)
{
    char    **linesplitted;
	char	*single_str;
	
		linesplitted = split_quotes(cmd_line);
		linesplitted = expand_and_trim(linesplitted);
		linesplitted = change_pipes(linesplitted);
		single_str = array_to_single_str(linesplitted);
		linesplitted = split_changed_pipes(single_str);
		// int x = 0;
		// while (linesplitted[x] != NULL)
		// {
		// 	printf("%s\n", linesplitted[x]);
		// 	x++;
		// }
		free_string_array(linesplitted);

		//EXEC//
}