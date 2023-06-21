/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:35:53 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 20:51:19 by delvira-         ###   ########.fr       */
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

void	norm_export_free(t_export exp)
{
	printf("too many arguments\n");
	free_string_array(exp.var);
}

void	norm_dela_norm(t_export exp)
{
	if (exp.x <= 1)
		norm_export(exp);
	else
		norm_export_free(exp);
}

void	exec_export(char	*cmd)
{
	t_export	exp;

	exp = init_export_vars(cmd);
	if (exp.x > 2 || exp.x <= 1)
	{
		norm_dela_norm(exp);
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

void	exec_only_export(void)
{
	int	x;

	x = 0;
	while (g_var.env[x])
	{
		if (ft_strncmp(g_var.env[x], "NULL", 4) != 0
			&& ft_strncmp(g_var.env[x], "?=", 2) != 0)
		{
			printf("declare -x ");
			printf("%s\n", g_var.env[x]);
		}
		x++;
	}
	g_var.exit_code = "0";
}
