/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:08:30 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 16:37:48 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_env(char	**env)
{
	char	**environ;
	int		x;
	char	*str;
	int		i;

	x = 0;
	environ = ft_calloc(1000, sizeof (char *));
	while (env[x])
	{
		i = 0;
		str = ft_calloc(1000, sizeof(char));
		while (env[x][i] != '\0')
		{
			str[i] = env[x][i];
			i++;
		}
		environ[x] = str;
		x++;
	}
	return (environ);
}

char	*path(void)
{
	int		i;
	int		k;
	char	cwd[1000];
	char	*pwd;
	char	*lastpath;

	k = 0;
	pwd = getcwd(cwd, 1000);
	i = 0;
	lastpath = ft_calloc(100, sizeof(char));
	while (pwd[i])
		i++;
	while (pwd[i] != '/')
		i--;
	i++;
	while (pwd[i] != '\0')
	{
		lastpath[k] = pwd[i];
		i++;
		k++;
	}
	lastpath[k] = ' ';
	lastpath[k + 1] = '>';
	lastpath[k + 2] = ' ';
	return (lastpath);
}
