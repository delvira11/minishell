/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:44:14 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/20 19:24:29 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_back_redir(char **cmd)
{
	int		i;
	int		j;
	char	*next_path;
	char	*prev_path;
	char	cwd[1000];

	i = 3;
	j = 0;
	next_path = ft_calloc(malloc_size(), sizeof(char));
	prev_path = cd_back();
	while (cmd[1][i] != '\0')
	{
		next_path[j] = cmd[1][i];
		i++;
		j++;
	}
	chdir(prev_path);
	chdir(next_path);
	free(next_path);
	next_path = getcwd(cwd, 1000);
	change_env_var("PWD=", next_path);
	free(prev_path);
}

void	cd_folder_2(char	*next_path, char	*pwd)
{
	if (chdir(next_path) >= 0)
		change_env_var("PWD=", next_path);
	else
		g_var.exit_code = "1";
	free(next_path);
	free (pwd);
}

void	cd_folder(char **cmd)
{
	t_counters	c;
	char		*pwd;
	char		*next_path;

	c.i = 4;
	c.x = 0;
	c.k = 0;
	pwd = ft_calloc(malloc_size(), sizeof(char));
	while (g_var.env[c.x])
	{
		if (ft_strncmp(g_var.env[c.x], "PWD=", 4) == 0)
		{
			while (g_var.env[c.x][c.i] != '\0')
			{
				pwd[c.k] = g_var.env[c.x][c.i];
				c.k++;
				c.i++;
			}
		}
		pwd[c.k] = '/';
		c.x++;
	}
	next_path = ft_strjoin(pwd, cmd[1]);
	cd_folder_2(next_path, pwd);
}

void	exec_cd_free(char **new_cmd, char *home)
{
	ft_printf("Error de argumentos. Intenta: cd [directorio]\n");
	free_string_array(new_cmd);
	free(home);
}

void	exec_cd(char *cmd)
{
	char	**new_cmd;
	char	*home;
	int		x;

	x = 0;
	home = get_home_path();
	new_cmd = ft_split(cmd, ' ');
	while (new_cmd[x])
		x++;
	if (x > 2)
	{
		exec_cd_free(new_cmd, home);
		return ;
	}
	if (!new_cmd[1])
	{
		if (chdir(home) >= 0)
			change_env_var("PWD=", home);
	}
	else if (new_cmd[0] && new_cmd[1])
		cd_2args(new_cmd);
	free(new_cmd[0]);
	if (!new_cmd[1])
		free(new_cmd);
	free(home);
}
