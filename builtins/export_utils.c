/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:10:02 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 20:52:12 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_utils_1(char	**var, char	**var_name_split, char *varnameigual)
{
	free_string_array(var_name_split);
	free(varnameigual);
	free(var);
	free(var[0]);
}

void	free_utils_2(char	**var_name_split, char	*varnameigual, char	**var)
{
	free_string_array(var_name_split);
	free(varnameigual);
	free_string_array(var);
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

void	norm_export(t_export exp)
{
	exec_only_export();
	free (exp.var[0]);
	free (exp.var);
}
