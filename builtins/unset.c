/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:32:51 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/22 17:40:12 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_norm(char **var, char *var_name)
{
	g_var.exit_code = "0";
	free_string_array(var);
	free(var_name);
}

void	unset_norm_2(char **var)
{
	free(var[0]);
	free(var);
	g_var.exit_code = "0";
	printf("arguments error\n");
}

void	exec_unset(char *cmd)
{
	char		**var;
	char		*var_name;
	t_counters	c;

	c.x = 0;
	c.j = 0;
	var = ft_split(cmd, ' ');
	while (var[c.j])
		c.j++;
	if (c.j <= 1 || c.j > 2)
	{
		unset_norm_2(var);
		return ;
	}
	var_name = ft_strjoin(var[1], "=");
	while (g_var.env[c.x])
	{
		if (ft_strncmp(g_var.env[c.x], var_name, ft_strlen(var_name)) == 0)
		{
			free(g_var.env[c.x]);
			g_var.env[c.x] = "NULL";
		}
		c.x++;
	}
	unset_norm(var, var_name);
}

// char	*norm_exec_utils(char **envp)
// {
// 	t_counters	c;
// 	char		*str;

// 	c.i = -1;
// 	while (envp[++c.i])
// 	{
// 		str = ft_strnstr(envp[c.i], "PATH=", 7);
// 		if (str != NULL)
// 			return (str);
// 	}
// 	return (NULL);
// }

// char	*ft_findpath(char *cmd, char **envp)
// {
// 	t_counters	c;
// 	t_path		p;

// 	c.x = -1;
// 	p.str = norm_exec_utils(envp);
// 	if (access(cmd, X_OK) == 0)
// 		return (cmd);
// 	if (!p.str)
// 		return (NULL);
// 	p.dir = ft_split(&p.str[5], ':');
// 	p.path2 = ft_strjoin("/", cmd);
// 	while (p.dir[++c.x])
// 	{
// 		p.path = ft_strjoin(p.dir[c.x], p.path2);
// 		c.i = access(p.path, X_OK);
// 		if (c.i == 0)
// 		{
// 			free(path);
// 			return (p.path);
// 		}
// 		free(p.path);
// 	}
// 	free(p.path2);
// 	free_string_array(p.dir);
// 	return (NULL);
// }