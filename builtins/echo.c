/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:51:22 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/19 20:54:04 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(char	*cmd)
{
	int		i;
	char	**split_cmd;

	i = 0;
	split_cmd = ft_split(cmd, ' ');
	if (ft_strncmp(split_cmd[1], "-n", 2) == 0)
	{
		i = 8;
		while (cmd[i + 2] != '\0')
		{
			write(1, &cmd[i], 1);
			i++;
		}
	}
	else
	{
		i = 5;
		while (cmd[i + 2] != '\0')
		{
			write(1, &cmd[i], 1);
			i++;
		}
		write(1, "\n", 1);
	}
	g_var.exit_code = "0";
	free_string_array(split_cmd);
}
