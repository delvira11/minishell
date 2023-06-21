/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:34:07 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/20 21:09:49 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	after_process_error(int error)
{
	if (error == 14 || error == 65280)
		g_var.exit_code = "127";
	else if (error == 256)
		g_var.exit_code = "1";
	else if (error != 0 && !(error == 14 || error == 65280 || error == 256))
		g_var.exit_code = "1";
	else
		g_var.exit_code = "0";
}

void	child_process_1(t_node *node, t_pip var, int tuberia[2])
{
	if (var.i == 0)
		get_first_infile(node, var.save);
	if (g_var.fix_nextfilein < 0)
		exit(0);
	if (var.i < var.max_nodes - 1)
		get_next_stdout(node, var.i, tuberia[1]);
	else
		get_last_stdout(node, var.i);
	close(tuberia[0]);
	close(tuberia[1]);
}

void	child_process_2(t_node *node, t_pip var, char **splittedarg)
{
	if (is_builtin(node[var.i].cmd))
	{
		exec_builtins(node[var.i].cmd);
		exit(0);
	}
	else
	{
		g_var.last_cmd_status = execve(ft_findpath(splittedarg[0], g_var.env),
				splittedarg, g_var.env);
		if (g_var.last_cmd_status < 0)
		{
			perror("command doesn't exist");
			exit(-1);
		}
	}
}

void	process_exec(t_node *node, t_pip var)
{
	int		tuberia[2];
	pid_t	process;
	char	**splittedarg;
	int		error;

	splittedarg = ft_split(node[var.i].cmd, ' ');
	pipe(tuberia);
	process = fork();
	if (process == 0)
	{
		child_process_1(node, var, tuberia);
		child_process_2(node, var, splittedarg);
	}
	error = errno;
	waitpid(process, &error, 0);
	after_process_error(error);
	if (is_builtin_env(node[var.i].cmd))
		exec_builtins_env(node[var.i].cmd);
	free_cmd_splitted(splittedarg);
	get_next_infile(node, var.i, tuberia[0], var.save);
	close(tuberia[0]);
	close(tuberia[1]);
}

void	exec_pipex(t_node	*node)
{
	t_pip	var;

	var.i = 0;
	while (node[var.i].cmd != NULL)
		var.i++;
	var.max_nodes = var.i;
	var.i = 0;
	var.save = dup(0);
	while (var.i < var.max_nodes)
	{
		process_exec(node, var);
		var.i++;
	}
	dup2(var.save, STDIN_FILENO);
}
