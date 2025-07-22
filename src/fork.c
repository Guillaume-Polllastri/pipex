/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:28:12 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/21 20:38:24 by gpollast         ###   ########.fr       */
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

void	create_pipes(t_pipe *pipefd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (pipe(pipefd[i].fd) == -1)
			return (perror("pipe"));
		i++;
	}
}

static void	setup_first_process(t_child *child, t_pipe *pipefd, t_info *info,
		int i)
{
	child[i].in = -1;
	child[i].out = pipefd[i].fd[1];
	execute_cmd(&child[i], info);
}

static void	setup_last_process(t_child *child, t_pipe *pipefd, t_info *info,
		int i)
{
	child[i].in = pipefd[i - 1].fd[0];
	child[i].out = open(info->arg[info->last_file],
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (child[i].out == -1)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	execute_cmd(&child[i], info);
}

static void	setup_middle_process(t_child *child, t_pipe *pipefd, t_info *info,
		int i)
{
	child[i].in = pipefd[i - 1].fd[0];
	child[i].out = pipefd[i].fd[1];
	execute_cmd(&child[i], info);
}

void	create_processes(t_child *child, t_pipe *pipefd, t_info *info)
{
	int	i;

	i = 0;
	while (i < (info->nb_cmd + 1))
	{
		child[i].pid = fork();
		if (child[i].pid == -1)
			return (perror("fork"));
		if (i == 0)
			setup_first_process(child, pipefd, info, i);
		else if (i == (info->nb_cmd))
			setup_last_process(child, pipefd, info, i);
		else
			setup_middle_process(child, pipefd, info, i);
		if (child[i].pid != 0)
		{
			if (child[i].in >= 0)
				close(child[i].in);
			if (child[i].out >= 0)
				close(child[i].out);
		}
		info->index_cmd++;
		i++;
	}
}
