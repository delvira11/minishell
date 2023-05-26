/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:10:02 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 16:10:30 by delvira-         ###   ########.fr       */
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
