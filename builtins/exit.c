/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:28:15 by ide-albe          #+#    #+#             */
/*   Updated: 2023/06/21 20:54:23 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_exit(void)
{
	g_var.exit_code = "1";
	printf("arguments error\n");
}

void	exec_exit(char *cmd)
{
	t_counters	c;
	char		**cmd_splitted;

	c.i = 0;
	c.j = -1;
	cmd_splitted = ft_split(cmd, ' ');
	while (cmd_splitted[c.i])
		c.i++;
	if (c.i == 1)
		exit(0);
	else if (c.i == 2)
	{
		while (cmd_splitted[1][++c.j])
		{
			if (cmd_splitted[1][c.j] > '9' || cmd_splitted[1][c.j] < '0')
			{
				printf("numeric argument required\n");
				g_var.exit_code = "255";
				return ;
			}
		}
		exit(ft_atoi(cmd_splitted[1]));
	}
	else
		norm_exit();
}
