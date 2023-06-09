/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:32:51 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 16:33:10 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(char	*cmd)
{
	int		x;
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
