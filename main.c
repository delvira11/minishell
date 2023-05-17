/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:33:15 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/17 13:27:59 by delvira-         ###   ########.fr       */
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

char	*history_append(char *history, char *cmd_line)
{
	char	*returnline;

	returnline = ft_strjoin(history, cmd_line);
	// returnline = ft_strjoin(returnline, "\n");
	return (returnline);
}

void	print_history(char *history_str)
{
	char	**splitted_cmd;
	int		x;
	int		j;

	j = 0;
	x = 0;
	splitted_cmd = ft_split(history_str, '\n');
	while (splitted_cmd[x])
		x++;
	x -= 1;
	if (x >= 16)
		j = x - 16;
	else
		j = 0;
	while (j < x)
	{
		printf("%s\n", splitted_cmd[j]);
		j++;
	}
}

int	main(int nargs, char **args, char **env)
{
	char		*cmd_line;

	signal(SIGINT, control_c);
	// signal(SIGQUIT, control_d);
	// init_global(env);
	while (1)
	{
		cmd_line = readline("minishell> ");
		if (cmd_line == NULL)
			break;
		parse_function(cmd_line);
		free(cmd_line);
		system("leaks -q minishell");
	}
		write(1, "dewt", 4);
	return (0);
}
