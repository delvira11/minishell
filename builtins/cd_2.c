/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:46:57 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/20 19:14:12 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_var(char	*name, char	*value)
{
	int		x;
	char	*str;
	int		i;
	int		j;

	x = 0;
	i = 0;
	j = 0;
	while (g_var.env[x])
	{
		if (!ft_strncmp(g_var.env[x], name, ft_strlen(name)))
		{
			str = ft_strjoin(name, value);
			free(g_var.env[x]);
			g_var.env[x] = str;
		}
		x++;
	}
}

void	cd_2args_2(char	**cmd)
{
	change_env_var("PWD=", cmd[1]);
	g_var.exit_code = "0";
}

void	cd_2args_free(char	**cmd)
{
	free (cmd[1]);
	free(cmd);
}

void	cd_2args(char **cmd)
{
	char	*diractual;
	char	cwd[1000];

	diractual = getcwd(cwd, 1000);
	if (ft_strncmp(cmd[1], "../", 3) == 0)
		cd_back_redir(cmd);
	else if (ft_strncmp(cmd[1], "..\0", 3) == 0)
		cd_back_noret();
	else if (ft_strncmp(cmd[1], "/", 1) == 0)
	{
		if (chdir(cmd[1]) >= 0 && ft_strncmp(diractual, "PWD=/", 5))
			cd_2args_2(cmd);
		else
			g_var.exit_code = "1";
	}
	else if ((ft_strncmp(cmd[1], ".", 1)) == 0)
	{
		free (cmd[1]);
		free(cmd);
		g_var.exit_code = "0";
		return ;
	}
	else
		cd_folder(cmd);
	cd_2args_free(cmd);
}

char	*get_home_path(void)
{
	t_counters	c;
	char		*home_path;

	c.x = 0;
	c.i = 0;
	home_path = ft_calloc (malloc_size(), sizeof(char));
	while (g_var.env[c.x])
	{
		if (ft_strncmp(g_var.env[c.x], "HOME=", 5) == 0)
		{
			while (g_var.env[c.x][c.i] != '=')
				c.i++;
			c.i++;
			c.k = 0;
			while (g_var.env[c.x][c.i] != '\0')
			{
				home_path[c.k++] = g_var.env[c.x][c.i++];
			}
			home_path[c.k] = '\0';
			break ;
		}
		c.x++;
	}
	return (home_path);
}
