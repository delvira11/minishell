/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-albe <ide-albe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:34:38 by delvira-          #+#    #+#             */
/*   Updated: 2023/06/21 17:05:02 by ide-albe         ###   ########.fr       */
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

char	*ft_findpath(char *cmd, char **envp)
{
	int		i;
	int		x;
	char	*str;
	char	*path;
	char	*path2;
	char	**dir;

	x = -1;
	i = -1;
	while (envp[++i])
	{
		str = ft_strnstr(envp[i], "PATH=", 7);
		if (str != NULL)
			break ;
	}
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!str)
		return (NULL);
	dir = ft_split(&str[5], ':');
	path2 = ft_strjoin("/", cmd);
	while (dir[++x])
	{
		path = ft_strjoin(dir[x], path2);
		i = access(path, X_OK);
		if (i == 0)
		{
			free(path);
			return (path);
		}
		free(path);
	}
	free(path2);
	free_string_array(dir);
	return (NULL);
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
