/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:08:30 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 17:55:21 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_env(char	**env)
{
	char	**environ;
	int		x;
	char	*str;
	int		i;

	x = 0;
	environ = ft_calloc(malloc_size(), sizeof (char *));
	while (env[x])
	{
		i = 0;
		str = ft_calloc(malloc_size(), sizeof(char));
		while (env[x][i] != '\0')
		{
			str[i] = env[x][i];
			i++;
		}
		environ[x] = str;
		x++;
	}
	return (environ);
}

char	*path(void)
{
	int		i;
	int		k;
	char	cwd[1000];
	char	*pwd;
	char	*lastpath;

	k = 0;
	pwd = getcwd(cwd, 1000);
	i = 0;
	lastpath = ft_calloc(malloc_size(), sizeof(char));
	while (pwd[i])
		i++;
	while (pwd[i] != '/')
		i--;
	i++;
	while (pwd[i] != '\0')
	{
		lastpath[k] = pwd[i];
		i++;
		k++;
	}
	lastpath[k] = ' ';
	lastpath[k + 1] = '>';
	lastpath[k + 2] = ' ';
	return (lastpath);
}

int	malloc_size(void)
{
	return (1000);
}

void	lvl_masuno(char *cmd_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strncmp(cmd_line, "./minishell", 11) == 0)
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
	}
}

void	lvl_masuno_bash(char *cmd_line)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strncmp(cmd_line, "bash", 4) == 0)
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
	}
}
