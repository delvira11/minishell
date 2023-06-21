/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:21:06 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 15:56:44 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(void)
{
	int	x;
	int	i;
	int	j;

	x = 0;
	i = 0;
	while (g_var.env[x])
	{
		while (g_var.env[i])
		{
			if (ft_strncmp(g_var.env[i], "SHLVL=", 6) == 0)
			{
				j = ft_strlen(g_var.env[i]);
				g_var.env[i][j - 1] = g_var.env[i][j - 1] + 1;
			}
			i++;
		}
		if (ft_strncmp(g_var.env[x], "NULL", 4) != 0
			&& ft_strncmp(g_var.env[x], "?=", 2) != 0)
			printf("%s\n", g_var.env[x]);
		x++;
	}
	g_var.exit_code = "0";
}
