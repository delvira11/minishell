/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:34:38 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 21:06:17 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_and_return_line(char	*line)
{
	free(line);
	return (NULL);
}

char	*ft_get_input(char *limit, int fd1, int save)
{
	char		*line;
	t_counters	c;

	line = "";
	while (line != NULL)
	{
		write(1, ">", 1);
		line = ft_get_next_line(save);
		if (!line)
			return (0);
		c.i = 0;
		c.j = 0;
		while (limit[c.i] != '\0')
			c.i++;
		if (ft_strncmp(line, limit, c.i) == 0)
			return (free_and_return_line(line));
		while (line[c.j] != '\0')
		{
			write(fd1, &line[c.j], 1);
			c.j++;
		}
		free(line);
	}
	close (fd1);
	return (line);
}

void	free_utils_path(t_path_var c)
{
	free(c.path2);
	free_string_array(c.dir);
}

t_path_var	free_utils_path_2(void)
{
	t_path_var	c;

	c.x = -1;
	c.i = -1;
	return (c);
}

char	*ft_findpath(char *cmd, char **envp)
{
	t_path_var	c;

	c = free_utils_path_2();
	while (envp[++c.i])
	{
		c.str = ft_strnstr(envp[c.i], "PATH=", 7);
		if (c.str != NULL)
			break ;
	}
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!c.str)
		return (NULL);
	c.dir = ft_split(&c.str[5], ':');
	c.path2 = ft_strjoin("/", cmd);
	while (c.dir[++c.x])
	{
		c.path = ft_strjoin(c.dir[c.x], c.path2);
		c.i = access(c.path, X_OK);
		if (c.i == 0)
			return (c.path);
		free(c.path);
	}
	free_utils_path(c);
	return (NULL);
}
