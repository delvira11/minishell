/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:34:07 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/25 20:25:43 by delvira-         ###   ########.fr       */
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

char	*free_and_return_line(char	*line)
{
	free(line);
	return (NULL);
}

char	*ft_get_input(char *limit, int fd1, int save)
{
	char	*line;
	int		i;
	int		j;

	line = "";
	while (line != NULL)
	{
		write(1, ">", 1);
		// ft_printf(">");
		line = ft_get_next_line(save);
		if (!line)
			return (0);
		i = 0;
		j = 0;
		while (limit[i] != '\0')
			i++;
		if (ft_strncmp(line, limit, i) == 0)
			return (free_and_return_line(line));
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

void	get_first_infile(t_node *node, int save)
{
	int	here_doc_fd;
	int	infile_fd;

	if (node[0].infile != NULL)
	{
		infile_fd = open(node[0].infile, O_RDONLY);
		if (infile_fd < 0)
		{
			perror("Couldn't open infile");
			exit(0);
		}
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		return ;
	}
	else if (node[0].delimiter != NULL)
	{
		here_doc_fd = open("in_heredoc.txt", O_RDWR | O_TRUNC | O_CREAT);
		ft_get_input(node[0].delimiter, here_doc_fd, save);
		close(here_doc_fd);
		here_doc_fd = open("in_heredoc.txt", O_RDONLY);
		dup2(here_doc_fd, STDIN_FILENO);
		close(here_doc_fd);
		return ;
	}
}

void	get_next_infile(t_node *node, int i, int tuberia, int save)
{
	int	here_doc_fd;
	int	infile_fd;

	g_var.fix_nextfilein = 1;
	if (node[i + 1].infile != NULL)
	{
		infile_fd = open(node[i + 1].infile, O_RDONLY);
		if (infile_fd < 0)
		{
			perror("Couldn't open infile");
			g_var.fix_nextfilein = -1;
			// exit(0);
		}
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		return ;
	}
	else if (node[i + 1].delimiter != NULL)
	{
		here_doc_fd = open("in_heredoc.txt", O_RDWR | O_TRUNC | O_CREAT);
		ft_get_input(node[i + 1].delimiter, here_doc_fd, save);
		close(here_doc_fd);
		here_doc_fd = open("in_heredoc.txt", O_RDONLY);
		dup2(here_doc_fd, STDIN_FILENO);
		close(here_doc_fd);
	}
	else
	{
		dup2(tuberia, STDIN_FILENO);
	}
}

t_node	*init_nodes(void)
{
	t_node	*node;

	node = ft_calloc(50, sizeof(t_node));
	node[0].infile = NULL;
	node[0].delimiter = NULL;
	node[0].outfile = NULL;
	node[0].outappend = NULL;
	node[0].cmd = "echo aaa";

	node[1].infile = NULL;
	node[1].delimiter = "fin";
	node[1].outfile = "out";
	node[1].outappend = NULL;
	node[1].cmd = "cat -e";

	node[2].infile = NULL;
	node[2].delimiter = NULL;
	node[2].outfile = NULL;
	node[2].outappend = NULL;
	node[2].cmd = "echo ccc";
	return (node);
}

void	get_next_stdout(t_node *node, int i, int tuberia)
{
	int	fd_out;

	if (node[i].outfile != NULL)
	{
		fd_out = open(node[i].outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (node[i].outappend != NULL)
	{
		fd_out = open(node[i].outappend, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else
		dup2(tuberia, STDOUT_FILENO);
}

void	get_last_stdout(t_node *node, int i)
{
	int	fd_out;

	if (node[i].outfile != NULL)
	{
		fd_out = open(node[i].outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (node[i].outappend != NULL)
	{
		fd_out = open(node[i].outappend, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}	
}

void	free_cmd_splitted(char	**split)
{
	int x;

	x = 0;
	while (split[x])
	{
		free(split[x]);
		x++;
	}
	free(split);
}

void	process_exec(t_node *node, int i, int max_nodes, int save)
{
	int		tuberia[2];
	pid_t	process;
	char	**splittedarg;
	int		error;

	splittedarg = ft_split(node[i].cmd, ' ');
	pipe(tuberia);
	process = fork();
	if (process == 0)
	{
		if (i == 0)
			get_first_infile(node, save);
		if (g_var.fix_nextfilein < 0)
			exit(0);
		if (i < max_nodes - 1)
			get_next_stdout(node, i, tuberia[1]);
		else
			get_last_stdout(node, i);
		close(tuberia[0]);
		close(tuberia[1]);
		if (is_builtin(node[i].cmd))
		{
			exec_builtins(node[i].cmd);
			exit(0);
		}
		else
		{
		g_var.last_cmd_status = execve(ft_findpath(splittedarg[0], g_var.env), splittedarg, g_var.env);
		if (g_var.last_cmd_status < 0)
		{
			perror("command doesn't exist");
			exit(-1);
		}
		}
	}
	error = errno;
	waitpid(process, &error, 0);
	if (error == 14 || error == 65280)
		g_var.exit_code = "127";
	else if (error == 256)
		g_var.exit_code = "1";
	else if (error != 0 && !(error == 14 || error == 65280 || error == 256))
		g_var.exit_code = "1";
	else
		g_var.exit_code = "0";
	if (is_builtin_env(node[i].cmd))
		exec_builtins_env(node[i].cmd);
	free_cmd_splitted(splittedarg);
	get_next_infile(node, i, tuberia[0], save);
	close(tuberia[0]);
	close(tuberia[1]);
}

void	exec_pipex(t_node	*node)
{
	// t_node	*node;
	int		i;
	int		save;
	int		max_nodes;

	// node = init_nodes();
	i = 0;
	while (node[i].cmd != NULL)
		i++;
	max_nodes = i;
	i = 0;
	save = dup(0);
	while (i < max_nodes)
	{
		process_exec(node, i, max_nodes, save);
		i++;
	}
	dup2(save, STDIN_FILENO);
	// free(node);
}
