/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:34:22 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 21:06:36 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_exit_code(void)
{
	int		x;
	int		i;
	char	*str;

	x = 0;
	i = 0;
	while (g_var.env[x])
		x++;
	str = ft_calloc(malloc_size(), sizeof(char));
	str[0] = '?';
	str[1] = '=';
	str[2] = '0';
	g_var.env[x] = str;
}

void	replace_exit_code(void)
{
	int		x;
	char	*str;
	int		i;
	int		j;

	x = -1;
	i = 2;
	j = 0;
	while (g_var.env[++x])
	{
		if (ft_strncmp(g_var.env[x], "?=", 2) == 0)
		{
			free(g_var.env[x]);
			str = ft_calloc(malloc_size(), sizeof(char));
			str[0] = '?';
			str[1] = '=';
			while (g_var.exit_code[j])
			{
				str[i] = g_var.exit_code[j];
				i++;
				j++;
			}
			g_var.env[x] = str;
		}
	}
}

void	free_cmd_splitted(char	**split)
{
	int	x;

	x = 0;
	while (split[x])
	{
		free(split[x]);
		x++;
	}
	free(split);
}
