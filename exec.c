/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:34:07 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/15 20:38:35 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char	*cmd)
{
	char	**splitted_cmd;

	splitted_cmd = ft_split(cmd, ' ');
	if (!ft_strncmp("echo", splitted_cmd[0], 4)
		&& !ft_strncmp("-n", splitted_cmd[1], 2))
		return (1);
	else if (!ft_strncmp("cd", splitted_cmd[0], 2))
		return (1);
	else if (!ft_strncmp("pwd", splitted_cmd[0], 3))
		return (1);
	else if (!ft_strncmp("export", splitted_cmd[0], 6))
		return (1);
	else if (!ft_strncmp("unset", splitted_cmd[0], 5))
		return (1);
	else if (!ft_strncmp("env", splitted_cmd[0], 3))
		return (1);
	else if (!ft_strncmp("exit", splitted_cmd[0], 4))
		return (1);
	return (0);
}

char	*ft_get_input(char *limit, int fd1)
{
	char	*line;
	int		i;
	int		j;

	line = "";
	while (line != NULL)
	{
		line = ft_get_next_line(0);
		if (!line)
			return (0);
		i = 0;
		j = 0;
		while (limit[i] != '\0')
			i++;
		if (ft_strncmp(line, limit, i) == 0)
			return (NULL);
		while (line[j] != '\0')
		{
			write(fd1, &line[j], 1);
			j++;
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
	char	**dir;

	x = -1;
	i = -1;
	while (envp[++i])
	{
		str = ft_strnstr(envp[i], "PATH=", 7);
		if (str != NULL)
			break ;
	}
	dir = ft_split(&str[5], ':');
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (dir[++x])
	{
		path = ft_strjoin(dir[x], ft_strjoin("/", cmd));
		i = access(path, X_OK);
		if (i == 0)
			return (path);
	}
	return (NULL);
}

char	*get_first_infile(t_node *node)
{
	int	here_doc_fd;

	if (node[0].infile != NULL)
	{
		return (node[0].infile);
	}
	else if (node[0].delimiter != NULL)
	{
		here_doc_fd = open("in_heredoc.txt", O_RDWR | O_TRUNC | O_CREAT);
		ft_get_input(node[0].delimiter, here_doc_fd);
		return ("in_heredoc.txt");
	}
	else
		return (NULL);
}



t_node	*init_nodes(void)
{
	t_node	*node;

	node = ft_calloc(50, sizeof(t_node));
	node[0].infile = "in";
	node[0].delimiter = NULL;
	node[0].outfile = NULL;
	node[0].cmd = "cat -e";

	node[1].infile = NULL;
	node[1].delimiter = NULL;
	node[1].outfile = NULL;
	node[1].cmd = "cat -e";

	node[2].infile = NULL;
	node[2].delimiter = NULL;
	node[2].outfile = NULL;
	node[2].cmd = "cat -e";
	return (node);
}

int	get_filein(t_node	*node, int i, int first_fd, int pip_fd)
{
	int	fd;
	int	here_doc_fd;

	if (i == 0)
		return (first_fd);
	else
	{
		if (node[i + 1].infile != NULL)
		{
			fd = open(node[i + 1].infile, O_RDONLY);
			close(fd);
			return (fd);
		}
		else if (node[i].delimiter != NULL)
		{
			here_doc_fd = open("in_heredoc.txt", O_RDWR | O_TRUNC | O_CREAT);
			ft_get_input(node[0].delimiter, here_doc_fd);
			fd = open("in_heredoc.txt", O_RDONLY);
			return (fd);
		}
		else if (node[i].outfile != NULL)
		{
			fd = open(node[i].outfile, O_RDONLY);
			close(fd);
			return (fd);
		}
		else
		{
			return (pip_fd);
		}
	}
}

int	get_fileout(t_node	*node, int i, int pip_fd)
{
	int	fd;

	// printf("\ni = %i", i);
	// printf("\n outfile : %s", node[i].outfile);
	if (node[i].outfile != NULL)
	{
		fd = open(node[i].outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		// close(fd);
		return (fd);
	}
	else
	{
		return (pip_fd);
	}
}

int	get_last_fileout(t_node *node, int i)
{
	int	return_fd;

	if (node[i].fileout != NULL)
	{
		if ()
	}
}

void	process_exec(t_node *node, int i, int first_fd, int max_nodes)
{
	int		tuberia[2];
	pid_t	process;
	char	**splittedarg;

	splittedarg = ft_split(node[i].cmd, ' ');
	pipe(tuberia);
	process = fork();
	if (process == 0)
	{
		if (i == 0)
			dup2(first_fd, STDIN_FILENO);
		if (i < max_nodes - 1)
			dup2(tuberia[1], STDOUT_FILENO);
		close(tuberia[0]);
		close(tuberia[1]);
		execve(ft_findpath(splittedarg[0], g_var.env), splittedarg, g_var.env);
	}
	waitpid(process, NULL, 0);
	dup2(tuberia[0], STDIN_FILENO);
	close(tuberia[0]);
	close(tuberia[1]);
}

void    exec_pipex()
{
	t_node	*node;
	int		i;
	int		save;
	int		max_nodes;
	int		first_fd;

	node = init_nodes();
	i = 0;
	while (node[i].cmd != NULL)
		i++;
	max_nodes = i;
	i = 0;
	save = dup(0);
	if (node[0].infile != NULL)
		first_fd = open(get_first_infile(node), O_RDWR);
	while (i < max_nodes)
	{
		process_exec(node, i, first_fd, max_nodes);
		i++;
	}
	dup2(save, STDIN_FILENO);
}
