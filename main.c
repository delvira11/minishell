/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:33:15 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/25 18:55:28 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_c(int n)
{
	n = SIGINT;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("   ", 1);
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// printf("\n");
	// rl_on_new_line();
	// rl_replace_line("", 1);
	// rl_redisplay();
}

void	control_d(int n)
{
	n = SIGQUIT;
	exit(0);
}

// char	*history_append(char *history, char *cmd_line)
// {
// 	char	*returnline;

// 	returnline = ft_strjoin(history, cmd_line);
// 	// returnline = ft_strjoin(returnline, "\n");
// 	return (returnline);
// }

// void	print_history(char *history_str)
// {
// 	char	**splitted_cmd;
// 	int		x;
// 	int		j;

// 	j = 0;
// 	x = 0;
// 	splitted_cmd = ft_split(history_str, '\n');
// 	while (splitted_cmd[x])
// 		x++;
// 	x -= 1;
// 	if (x >= 16)
// 		j = x - 16;
// 	else
// 		j = 0;
// 	while (j < x)
// 	{
// 		printf("%s\n", splitted_cmd[j]);
// 		j++;
// 	}
// }

char	**init_env(char	**env)
{
	char	**environ;
	int		x;
	char	*str;
	int		i;

	x = 0;
	environ = ft_calloc(1000, sizeof (char *));
	while (env[x])
	{
		i = 0;
		str = ft_calloc(1000, sizeof(char));
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

void	exec_env(void)
{
	int	x;

	x = 0;
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], "NULL", 4) != 0)
			printf("%s\n", g_var.env[x]);
		x++;
	}
}

void	exec_export(char	*cmd)
{
	char	**var;
	char	**var_name_split;
	char	*varnameigual;
	int		x;

	x = 0;
	var = ft_split(cmd, ' ');
	var_name_split = ft_split(var[1], '=');
	varnameigual = ft_strjoin(var_name_split[0], "=");
	while (var[x])
		x++;
	if (x > 2)
	{
		printf("arguments error\n");
		free_string_array(var_name_split);
		free(varnameigual);
		free_string_array(var);
		return ;
	}
	x = 0;
	if (!ft_strchr(var[1], '='))
	{
		free_string_array(var_name_split);
		free(varnameigual);
		free_string_array(var);
		return ;
	}
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], varnameigual, ft_strlen(varnameigual)) == 0)
		{
			free(g_var.env[x]);
			g_var.env[x] = var[1];
			free_string_array(var_name_split);
			free(varnameigual);
			free(var);
			free(var[0]);
			return ;
		}
		x++;
	}
	g_var.env[x] = var[1];
	free_string_array(var_name_split);
	free(varnameigual);
	free(var);
	free(var[0]);
}

void	exec_unset(char	*cmd)
{
	int	x;
	char	**var;
	char	*var_name;

	x = 0;
	var = ft_split(cmd, ' ');
	var_name = ft_strjoin(var[1], "=");
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], var_name, ft_strlen(var_name)) == 0)
		{
			free(g_var.env[x]);
			g_var.env[x] = "NULL";
		}
		x++;
	}
	free_string_array(var);
	free(var_name);
}

void	ft_leaks()
{
	system("leaks -q minishell");
}

char	*path()
{
	int		i;
	int		k;
	char	*cwd[1000];
	char	*pwd;
	char	*lastpath;

	k = 0;
	pwd = getcwd(cwd, 1000);
	// i = ft_strlen(pwd);
	i = 0;
	lastpath = ft_calloc(100, sizeof(char));
	while (pwd[i])
		i++;
	while(pwd[i] != '/')
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

void	create_exit_code()
{
	int	x;
	int i;

	char	*str;
	x = 0;
	i = 0;
	while (g_var.env[x])
		x++;
	str = ft_calloc(1000, sizeof(char));
	str[0] = '?';
	str[1] = '=';
	str[2] = '0';
	g_var.env[x] = str;
}

void	replace_exit_code()
{
	int		x;
	char	*str;
	int		i;
	int		j;

	x = 0;
	i = 2;
	j = 0;
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], "?=", 2) == 0)
		{
			free(g_var.env[x]);
			str = ft_calloc(1000, sizeof(char));
			str[0] = '?';
			str[1] = '=';
			while (g_var.exit_code[j])
			{
				str[i] = g_var.exit_code[j];
				i++;
				j++;
			}
			g_var.env[x] = str;
		}
		x++;
	}
}

int	main(int nargs, char **args, char **env)
{
	char		*cmd_line;
	char		*lastpath;
	// atexit(ft_leaks);

	signal(SIGINT, control_c);
	signal(SIGQUIT, control_d);
	// init_global(env);
	g_var.env = init_env(env);
	g_var.exit_code = "0";
	create_exit_code();
	while (1)
	{
		replace_exit_code();
		lastpath = path();
		cmd_line = readline(lastpath);
		add_history(cmd_line);
		if (cmd_line == NULL)
			break ;
		parse_function(cmd_line);
		free(cmd_line);
		free(lastpath);
		ft_leaks();
	}
	return (0);
}
