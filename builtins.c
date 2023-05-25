/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:28:15 by ide-albe          #+#    #+#             */
/*   Updated: 2023/05/25 18:56:17 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(char	*cmd)
{
	if (ft_strncmp("pwd ", cmd, 4) == 0)
		exec_pwd();
	if (ft_strncmp("env ", cmd, 4) == 0)
		exec_env();
	if (ft_strncmp("echo ", cmd, 5) == 0)
		exec_echo(cmd);
	return (0);
}

int	exec_builtins_env(char	*cmd)
{
	if (ft_strncmp("cd ", cmd, 3) == 0)
		exec_cd(cmd);
	if (ft_strncmp("export ", cmd, 7) == 0)
		exec_export(cmd);
	if (ft_strncmp("unset ", cmd, 6) == 0)
		exec_unset(cmd);
	if (ft_strncmp("exit", cmd, 4) == 0)
		exec_exit();
}

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
	// free(str);
}

void	cd_back_redir(char **cmd)
{
	int		i;
	int		j;
	char	*next_path;
	char	*prev_path;
	char	cwd[1000];

	i = 3;
	j = 0;
	next_path = ft_calloc(1000, sizeof(char));
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

void	cd_folder(char **cmd)
{
	int	i;
	int	x;
	int	k;
	char *pwd;
	char *next_path;

	i = 4;
	x = 0;
	k = 0;
	pwd = ft_calloc(1000, sizeof(char));
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], "PWD=", 4) == 0)
		{
			while (g_var.env[x][i] != '\0')
			{
				pwd[k] = g_var.env[x][i];
				k++;
				i++;
			}
		}
		pwd[k] = '/';
		x++;
	}
	next_path = ft_strjoin(pwd, cmd[1]);
	if (chdir(next_path) >= 0)
		change_env_var("PWD=", next_path);
	free(next_path);
	free (pwd);
}

void	cd_2args(char **cmd)
{
	char 	*diractual;
	char	cwd[1000];

	diractual = getcwd(cwd, 1000);
	if (ft_strncmp(cmd[1], "../", 3) == 0)
		cd_back_redir(cmd);
	else if (ft_strncmp(cmd[1], "..\0", 3) == 0)
		cd_back_noret();
	else if (ft_strncmp(cmd[1], "/", 1) == 0)
	{
		if (chdir(cmd[1]) >= 0 && ft_strncmp(diractual, "PWD=/", 5))
			change_env_var("PWD=", cmd[1]);
		g_var.exit_code = "0";
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
		free (cmd[1]);
		free(cmd);
		g_var.exit_code = "0";
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
		ft_printf("Error de argumentos. Intenta: cd [directorio]\n");
		free_string_array(new_cmd);
		free(home);
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

char	*get_home_path(void)
{
	int		x;
	int		i;
	int		k;
	char	*home_path;

	x = 0;
	i = 0;
	home_path = malloc (1000 * sizeof(char));
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], "HOME=", 5) == 0)
		{
			while (g_var.env[x][i] != '=')
				i++;
			i++;
			k = 0;
			while (g_var.env[x][i] != '\0')
			{
				home_path[k++] = g_var.env[x][i++];
			}
			home_path[k] = '\0';
			break ;
		}
		x++;
	}
	return (home_path);
}

char	*cd_back(void)
{
	int		i;
	int		x;
	int		k;
	int		j;
	char	*prev_path;

	i = 0;
	x = 0;
	k = 0;
	j = 4;
	prev_path = ft_calloc(1000, sizeof(char));
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], "PWD=", 4) == 0)
		{
			if (ft_strncmp(g_var.env[x], "PWD=/\0", 6) == 0)
				return (0);
			i = ft_strlen(g_var.env[x]) - 2;
			while (g_var.env[x][i] != '/')
				i--;
			while (j != i + 1)
				prev_path[k++] = g_var.env[x][j++];
		}
		x++;
	}
	if (chdir(prev_path) >= 0)
		change_env_var("PWD=", prev_path);
	return (prev_path);
}

void	cd_back_noret(void)
{
	int		i;
	int		x;
	int		k;
	int		j;
	char	*prev_path;

	i = 0;
	x = 0;
	k = 0;
	j = 4;
	prev_path = ft_calloc(1000, sizeof(char));
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], "PWD=", 4) == 0)
		{
			if (ft_strncmp(g_var.env[x], "PWD=/\0", 6) == 0)
			{
				free(prev_path);
				return ;
			}
			i = ft_strlen(g_var.env[x]) - 2;
			while (g_var.env[x][i] != '/')
				i--;
			while (j != i + 1)
				prev_path[k++] = g_var.env[x][j++];
		}
		x++;
	}
	if (chdir(prev_path) >= 0)
		change_env_var("PWD=", prev_path);
	free(prev_path);
}

int		exec_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, 1000))
	{
		ft_putendl_fd(cwd, 1);
		return (1);
	}
	else
		return (-1);
}

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
	free_string_array(split_cmd);
}

void	exec_exit(void)
{
	exit(0);
}
