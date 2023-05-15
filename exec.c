/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:34:07 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/11 18:34:56 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


t_node	*init_nodes(void)
{
	t_node	*node;

	node = ft_calloc(50, sizeof(t_node));
	node[0].infile = "in";
	node[0].delimiter = NULL;
	node[0].outfile = "outfile";
	node[0].cmd = "cat -e";

	node[1].infile = NULL;
	node[1].delimiter = NULL;
	node[1].outfile = "outfile2";
	node[1].cmd = "echo bbb";

	node[2].infile = NULL;
	node[2].delimiter = NULL;
	node[2].outfile = "out";
	node[2].cmd = "echo ccc";
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

void	loop_process(t_node *node, char **envp, int i, int first_fd)
{
	pid_t	pid;
	int		fd[2];
	char	**splitedarg;
	int		execerror;
	int		x;
	splitedarg = ft_split(node[i].cmd, ' ');
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(get_fileout(node, i, fd[1]), STDOUT_FILENO);
		// write(1, "\neyy", 4);
		execerror = execve(ft_findpath(splitedarg[0], envp), splitedarg, envp);
		if (execerror < 0)
			printf("error cmd");
		// ft_free_split(splitedarg);
	}
	else
	{
	// write(1, "\naaa", 4);
		// write(1, "hola", 4);
		close(fd[1]);
		dup2(get_filein(node, i, first_fd, fd[0]), STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void    exec_pipex()
{
	t_node	*node;
	int		fdin;
	int i = 0;
	node = init_nodes();

	// printf("get_first_infile: %s", get_first_infile(node));
	fdin = open(get_first_infile(node), O_RDONLY);
	dup2(fdin, STDIN_FILENO);
	// dup2(0, STDIN_FILENO);
	// close(fdin);
	while (i < 3)
	{
		loop_process(node, g_var.env, i, fdin);
		i++;
	}
}
