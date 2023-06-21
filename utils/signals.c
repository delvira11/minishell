/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:30:38 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 20:18:47 by delvira-         ###   ########.fr       */
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
}

void	shlvl_increase(char *cmd_line)
{
	lvl_masuno(cmd_line);
	lvl_masuno_bash(cmd_line);
}

void	signals(void)
{
	signal(SIGINT, control_c);
	signal(SIGQUIT, SIG_IGN);
}
