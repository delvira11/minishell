/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:21:06 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 16:22:00 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	g_var.exit_code = "0";
}
