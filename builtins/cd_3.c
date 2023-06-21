/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:49:14 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/20 19:56:50 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_back(void)
{
	t_counters	c;
	char		*prev_path;

	c.i = 0;
	c.x = 0;
	c.k = 0;
	c.j = 4;
	prev_path = ft_calloc(malloc_size(), sizeof(char));
	while (g_var.env[c.x])
	{
		if (ft_strncmp(g_var.env[c.x], "PWD=", 4) == 0)
		{
			if (ft_strncmp(g_var.env[c.x], "PWD=/\0", 6) == 0)
				return (0);
			c.i = ft_strlen(g_var.env[c.x]) - 2;
			while (g_var.env[c.x][c.i] != '/')
				c.i--;
			while (c.j != c.i + 1)
				prev_path[c.k++] = g_var.env[c.x][c.j++];
		}
		c.x++;
	}
	if (chdir(prev_path) >= 0)
		change_env_var("PWD=", prev_path);
	return (prev_path);
}

t_counters	cd_back_noret_counters(void)
{
	t_counters	c;

	c.i = 0;
	c.x = 0;
	c.k = 0;
	c.j = 4;
	return (c);
}

void	cd_back_noret(void)
{
	t_counters	c;
	char		*prev_path;

	c = cd_back_noret_counters();
	prev_path = ft_calloc(malloc_size(), sizeof(char));
	while (g_var.env[c.x])
	{
		if (ft_strncmp(g_var.env[c.x], "PWD=", 4) == 0)
		{
			if (ft_strncmp(g_var.env[c.x], "PWD=/\0", 6) == 0)
			{
				free(prev_path);
				return ;
			}
			c.i = ft_strlen(g_var.env[c.x]) - 2;
			while (g_var.env[c.x][c.i] != '/')
				c.i--;
			while (c.j != c.i + 1)
				prev_path[c.k++] = g_var.env[c.x][c.j++];
		}
		c.x++;
	}
	if (chdir(prev_path) >= 0)
		change_env_var("PWD=", prev_path);
	free(prev_path);
}
