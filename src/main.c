/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:54:05 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/17 17:13:01 by gpollast         ###   ########.fr       */
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
#include "get_next_line.h"

static int	child1(pid_t pid, int *pipefd, char **av)
{
	char	*path;
	char	**cmd;

	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		path = cmd_path(av[2]);
		cmd = ft_split(av[2], " \t");
		execve(path, cmd, NULL);
		perror("Error\nEnfant 1 Invalid command ");
		return (0);
	}
	return (0);
}

static int	child2(pid_t pid, int *pipefd, char **av)
{
	char	*path;
	char	**cmd;

	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		path = cmd_path(av[3]);
		cmd = ft_split(av[3], " \t");
		execve(path, cmd, NULL);
		perror("Error\nEnfant 2 Invalid command ");
		return (0);
	}
	return (0);
}

static int	parent(pid_t pid, int status, int *pipefd)
{
	int		fd;
	char	*line;

	line = get_next_line(pipefd[0]);
	fd = open("file2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Error\n"), 1);
	while (line)
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(pipefd[0]);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
	waitpid(pid, &status, 0);
	printf("Enfant 2 terminé\n");
	printf("Les deux Enfants ont été crées\n");
	return (1);
}

int	main(int ac, char **av)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		pipefd[2];

	if (ac == 5)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid1 = fork();
		child1(pid1, pipefd, av);
		waitpid(pid1, &status, 0);
		printf("Enfant 1 terminé\n");
		pid2 = fork();
		child2(pid2, pipefd, av);
		parent(pid2, status, pipefd);
		return (0);
	}
	printf("Error\nThe program needs 4 arguments\n");
	return (0);
}
