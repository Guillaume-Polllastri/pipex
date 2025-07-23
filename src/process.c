/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:41:31 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/23 16:45:51 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_printf.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

void	close_unused_pipes(t_pipe *pipefd, int nb_cmd, int keep_read,
		int keep_write)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (pipefd[i].fd[0] != keep_read)
			close(pipefd[i].fd[0]);
		if (pipefd[i].fd[1] != keep_write)
			close(pipefd[i].fd[1]);
		i++;
	}
}

void	execute_cmd(t_child *child, t_info *info, t_pipe *pipefd)
{
	if (child->pid == 0)
	{
		close_unused_pipes(pipefd, info->nb_cmd, child->in, child->out);
		setup_redirections(child);
		exec_command(child, info);
	}
}

void	close_pipes(t_pipe *pipefd, int nb_cmd)
{
	int	i;

	i = -1;
	while (++i < nb_cmd)
	{
		close(pipefd[i].fd[0]);
		close(pipefd[i].fd[1]);
	}
}

void	free_child(t_child *child)
{
	free(child->path_cmd);
	free_string_array(child->cmd);
}

void	parent(t_info *info)
{
	t_pipe	*pipefd;
	t_child	*children;

	pipefd = malloc(sizeof(t_pipe) * (info->nb_cmd));
	if (!pipefd)
	{
		perror("Error\nAllocating memory for pipes ");
		exit(EXIT_FAILURE);
	}
	create_pipes(pipefd, info->nb_cmd);
	children = setup_childs(info);
	create_processes(children, pipefd, info);
	close_pipes(pipefd, info->nb_cmd);
	wait_children(children, info->nb_cmd);
	cleanup_children(children, info->nb_cmd);
	free(children);
	free(pipefd);
}
