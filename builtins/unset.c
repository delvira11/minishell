/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:32:51 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/19 19:40:41 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_unset(char	*cmd)
{
	int		x;
	char	**var;
	char	*var_name;
	int		j;

	x = 0;
	j = 0;
	var = ft_split(cmd, ' ');
	while (var[j])
		j++;
	if (j <= 1)
	{
		free (var[0]);
		free (var);
		return ;
	}
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
