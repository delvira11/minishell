/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:33:15 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 21:06:58 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_leaks(void)
{
	system("leaks -q minishell");
}

int	main(int nargs, char **args __attribute__((unused)), char **env)
{
	char		*cmd_line;
	char		*lastpath;

	if (nargs != 1)
		exit(0);
	g_var.exit_code = "0";
	signals();
	g_var.env = init_env(env);
	create_exit_code();
	while (1)
	{
		replace_exit_code();
		lastpath = path();
		cmd_line = readline(lastpath);
		add_history(cmd_line);
		if (cmd_line == NULL)
			break ;
		g_var.cmd_size = ft_strlen(cmd_line);
		shlvl_increase(cmd_line);
		parse_function(cmd_line);
		free(cmd_line);
		free(lastpath);
	}
	free(lastpath);
	return (ft_atoi(g_var.exit_code));
}
