/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:35:53 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/19 20:53:08 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	init_export_vars(char	*cmd)
{
	t_export	exp;	

	exp.x = 0;
	exp.var = ft_split(cmd, ' ');
	while (exp.var[exp.x])
		exp.x++;
	if (exp.x > 2 || exp.x <= 1)
		return (exp);
	exp.var_name_split = ft_split(exp.var[1], '=');
	exp.varnameigual = ft_strjoin(exp.var_name_split[0], "=");
	return (exp);
}

void	norm_export_1(t_export exp)
{
	free(g_var.env[exp.x]);
	g_var.env[exp.x] = exp.var[1];
	free_utils_1(exp.var, exp.var_name_split, exp.varnameigual);
}

void	norm_export_2(t_export exp)
{
	g_var.env[exp.x] = exp.var[1];
	free_utils_1(exp.var, exp.var_name_split, exp.varnameigual);
}

void	exec_export(char	*cmd)
{
	t_export	exp;

	exp = init_export_vars(cmd);
	if (exp.x > 2 || exp.x <= 1)
	{
		if (exp.x <= 1)
		{
			free (exp.var[0]);
			free (exp.var);
		}
		else
			free_utils_2(exp.var_name_split, exp.varnameigual, exp.var);
		printf("export argument error\n");
		return ;
	}
	exp.x = 0;
	if (!ft_strchr(exp.var[1], '='))
	{
		free_utils_2(exp.var_name_split, exp.varnameigual, exp.var);
		return ;
	}
	while (g_var.env[exp.x])
	{
		if (ft_strncmp(g_var.env[exp.x], exp.varnameigual,
				ft_strlen(exp.varnameigual)) == 0)
		{
			norm_export_1(exp);
			return ;
		}
		exp.x++;
	}
	norm_export_2(exp);
}
