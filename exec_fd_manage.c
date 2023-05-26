/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delvira- <delvira-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:38:07 by delvira-          #+#    #+#             */
/*   Updated: 2023/05/26 19:38:34 by delvira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	norm_filein_error(void)
{
	perror("Couldn't open infile");
	g_var.fix_nextfilein = -1;
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
			norm_filein_error();
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
		dup2(tuberia, STDIN_FILENO);
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
