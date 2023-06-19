/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:28:15 by ide-albe          #+#    #+#             */
/*   Updated: 2023/06/19 20:11:01 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(char *cmd)
{
	int		i;
	int		j;
	char	**cmd_splitted;

	i = 0;
	j = 0;
	cmd_splitted = ft_split(cmd, ' ');
	while (cmd_splitted[i])
		i++;
	if (i == 1)
	{
		exit(0);	
	}
	else if (i == 2)
	{
		while (cmd_splitted[1][i++])
		{
			if (cmd_splitted[1][i] > 57 || cmd_splitted[1][i] < 48)
			{
				printf("numeric argument required\n");
				g_var.exit_code = "255";
				return ;
			}
		}
		exit(ft_atoi(cmd_splitted[1]));
	}
	else
	{
		printf("arguments error\n");
	}
}
