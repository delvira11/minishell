/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:33:05 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/20 20:28:10 by ide-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char	*cmd)
{
	if (!ft_strncmp("echo ", cmd, 5))
		return (1);
	else if (!ft_strncmp("cd ", cmd, 3))
		return (1);
	else if (!ft_strncmp("pwd ", cmd, 4))
		return (1);
	else if (!ft_strncmp("export ", cmd, 7))
		return (1);
	else if (!ft_strncmp("unset ", cmd, 6))
		return (1);
	else if (!ft_strncmp("env ", cmd, 4))
		return (1);
	else if (!ft_strncmp("exit ", cmd, 5))
		return (1);
	return (0);
}

int	is_builtin_env(char	*cmd)
{
	if (!ft_strncmp("cd", cmd, 2))
		return (1);
	if (!ft_strncmp("export", cmd, 6))
		return (1);
	if (!ft_strncmp("unset", cmd, 5))
		return (1);
	if (!ft_strncmp("exit", cmd, 4))
		return (1);
	return (0);
}

int	exec_builtins(char	*cmd)
{
	if (ft_strncmp("pwd ", cmd, 4) == 0)
		exec_pwd();
	if (ft_strncmp("env ", cmd, 4) == 0)
		exec_env();
	if (ft_strncmp("echo ", cmd, 5) == 0)
		exec_echo(cmd);
	return (0);
}

int	exec_builtins_env(char	*cmd)
{
	if (ft_strncmp("cd ", cmd, 3) == 0)
		exec_cd(cmd);
	if (ft_strncmp("export ", cmd, 7) == 0)
		exec_export(cmd);
	if (ft_strncmp("unset ", cmd, 6) == 0)
		exec_unset(cmd);
	if (ft_strncmp("exit", cmd, 4) == 0)
		exec_exit(cmd);
	return (0);
}
