/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:33:15 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 20:57:39 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int nargs, char **args __attribute__((unused)), char **env)
{
	char		*cmd_line;
	char		*lastpath;

	if (nargs != 1)
		exit(0);
	signal(SIGINT, control_c);
	signal(SIGQUIT, control_d);
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
		system("leaks -q minishell");
	}
	return (0);
}
