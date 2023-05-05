/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:33:15 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/05 18:20:47 by delvira-         ###   ########.fr       */
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

int	main( void )
{
	char		*cmd_line;
	char		*history;

	history = "";
	// char		path[1024];

	// getcwd(path, 1024);
	// printf("PATH: %s\n", path);
	signal(SIGINT, control_c);
	// signal(SIGQUIT, control_d);

	while (1)
	{
		cmd_line = readline("minishell> ");
		// history = history_append(history, cmd_line);
		// if (!ft_strncmp("history", ft_strtrim(cmd_line, " "), 5))
		// 	print_history(history);
		if (!cmd_line)
			break ;
		split_quotes(cmd_line);
		free(cmd_line);
		// system("leaks -q minishell");
	}
	// free (history);
}