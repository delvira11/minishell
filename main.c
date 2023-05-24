/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:33:15 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/24 20:05:33 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_c(int n)
{
	n = SIGINT;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
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

	x = 0;
	environ = ft_calloc(1000, sizeof (char *));
	while (env[x])
	{
		environ[x] = env[x];
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
		return ;
	}
	x = 0;
	if (!ft_strchr(var[1], '='))
	{
		return ;
	}
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], varnameigual, ft_strlen(varnameigual)) == 0)
		{
			g_var.env[x] = var[1];
			return ;
		}
		x++;
	}
	g_var.env[x] = var[1];
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
			// free(g_var.env[x]);
			g_var.env[x] = "NULL";
		}
		x++;
	}
}

int	main(int nargs, char **args, char **env)
{
	char		*cmd_line;

	signal(SIGINT, control_c);
	signal(SIGQUIT, control_d);
	// init_global(env);
	g_var.env = init_env(env);
	while (1)
	{
		cmd_line = readline("minishell> ");
		add_history(cmd_line);
		if (cmd_line == NULL)
			break ;
		parse_function(cmd_line);
		free(cmd_line);
		system("leaks -q minishell");
	}
	return (0);
}
