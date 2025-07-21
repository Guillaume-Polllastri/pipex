/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:41:31 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/21 20:30:41 by gpollast         ###   ########.fr       */
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

void	execute_cmd(t_child *child, t_info *info)
{
	if (child->pid == 0)
	{
		if (child->in >= 0)
		{
			dup2(child->in, STDIN_FILENO);
			close(child->in);
		}
		dup2(child->out, STDOUT_FILENO);
		close(child->out);
		if (child->path_cmd)
		{
			fprintf(stderr, "execute child %s\n", child->path_cmd);
			execve(child->path_cmd, child->cmd, NULL);
		}
		else
		{
			fprintf(stderr, "execute function\n");
			child->f(info);
		}
		perror("Error\nCommand is invalid ");
		exit(EXIT_FAILURE);
	}
}

void	free_child(t_child *child)
{
	free(child->path_cmd);
	free_string_array(child->cmd);
}

static void	execute_heredoc(t_info *info)
{
	(void)info;
}

#define BUFFER_SIZE 4096

static void	execute_read_file(t_info *info)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	int		len;

	fd = open(info->arg[1], O_RDONLY);
	len = read(fd, buffer, BUFFER_SIZE);
	while (len > 0)
	{
		write(1, buffer, len);
		len = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	exit(0);
}

static t_child	*setup_childs(t_info *info)
{
	t_child	*children;
	int		i;

	children = malloc(sizeof(t_child) * info->nb_cmd + 1);
	ft_bzero(&children[0], sizeof(*children));
	if (!ft_strncmp(info->arg[1], "here_doc", ft_strlen(info->arg[1])))
		children[0].f = execute_heredoc;
	else
		children[0].f = execute_read_file;
	i = 0;
	while (i < info->nb_cmd)
	{
		children[i + 1].path_cmd = cmd_path(info->arg[info->index_cmd + i]);
		children[i + 1].cmd = ft_split(info->arg[info->index_cmd + i], " \t");
		i++;
	}
	return (children);
}

void	parent(t_info *info)
{
	t_pipe	*pipefd;
	t_child	*children;
	int		i;

	pipefd = malloc(sizeof(t_pipe) * (info->nb_cmd));
	create_pipes(pipefd, info->nb_cmd);
	children = setup_childs(info);
	create_processes(children, pipefd, info);
	i = 0;
	while (i < info->nb_cmd)
	{
		waitpid(children[i].pid, &children[i].status, 0);
		ft_printf("Enfant %d a terminé avec status : %d\n", i, children[i].status);
		i++;
	}
	ft_printf("Les Enfants ont été crées\n");
	free(children);
	free(pipefd);
}
