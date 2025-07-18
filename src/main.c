/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:54:05 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/18 19:57:15 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	find_cmd(t_child *child, char **av, int index)
{
	child->path_cmd = cmd_path(av[index]);
	child->cmd = ft_split(av[index], " \t");
}

static void	execute_cmd(t_child *child)
{
	if (child->pid == 0)
	{
		dup2(child->in, STDIN_FILENO);
		close(child->in);
		dup2(child->out, STDOUT_FILENO);
		close(child->out);
		execve(child->path_cmd, child->cmd, NULL);
		perror("Error\nCommand is invalid ");
		exit(EXIT_FAILURE);
	}
}

static void	parent(char **av, int nb_cmd, int file2)
{
	t_child	*child;
	t_pipe	*pipefd;
	int		i;

	child = malloc(sizeof(t_child) * nb_cmd);
	pipefd = malloc(sizeof(t_pipe) * (nb_cmd - 1));
	i = 0;
	while (i < (nb_cmd - 1))
	{
		if (pipe(pipefd[i].fd) == -1)
			return (perror("pipe"));
		i++;
	}
	i = 0;
	while (i < nb_cmd)
	{
		child[i].pid = fork();
		if (child[i].pid == -1)
			return (perror("fork"));
		if (i == 0)
		{
			child[i].in = open(av[1], O_RDONLY);
			child[i].out = pipefd[i].fd[1];
			find_cmd(&child[i], av, i + 2);
			execute_cmd(&child[i]);
			close(pipefd[i].fd[1]);
		}
		else if (i == (nb_cmd - 1))
		{
			child[i].in = pipefd[i - 1].fd[0];
			child[i].out = open(av[file2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			find_cmd(&child[i], av, i + 2);
			execute_cmd(&child[i]);
			close(pipefd[i - 1].fd[0]);
		}
		else
		{
			child[i].in = pipefd[i - 1].fd[0];
			child[i].out = pipefd[i].fd[1];
			find_cmd(&child[i], av, i + 2);
			execute_cmd(&child[i]);
			close(pipefd[i - 1].fd[0]);
			close(pipefd[i].fd[1]);
		}
		i++;
	}
	i = 0;
	while (i < nb_cmd)
	{
		waitpid(child[i].pid, &child[i].status, 0);
		printf("Enfant a terminé avec status : %d\n", child[i].status);
		i++;
	}
	printf("Les Enfants ont été crées\n");
	free(child);
	free(pipefd);
}

int	main(int ac, char **av)
{
	if (ac >= 5)
	{
		parent(av, ac - 3, ac - 1);
		return (0);
	}
	printf("Error\nThe program needs 4 arguments\n");
	return (0);
}
