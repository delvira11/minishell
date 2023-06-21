/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:51:22 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 16:57:21 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(char	*cmd)
{
	int		i;
	char	**split_cmd;
	int		x;

	i = 0;
	split_cmd = ft_split(cmd, ' ');
	if (ft_strncmp(split_cmd[1], "-n", 2) == 0)
	{
		x = 2;
		while (split_cmd[x])
		{
			ft_putstr_fd(split_cmd[x], 1);
			x++;
		}
		// i = 8;
		// while (cmd[i + 2] != '\0')
		// {
		// 	write(1, &cmd[i], 1);
		// 	i++;
		// }
	}
	else
	{
		x = 1;
		while (split_cmd[x])
		{
			ft_putstr_fd(split_cmd[x], 1);
			x++;
		}
		write(1, "\n", 1);
	}
	g_var.exit_code = "0";
	free_string_array(split_cmd);
}
