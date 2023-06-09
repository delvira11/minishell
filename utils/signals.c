/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:30:38 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 16:31:06 by delvira-         ###   ########.fr       */
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

void	control_d(int n)
{
	n = SIGQUIT;
	exit(0);
}
