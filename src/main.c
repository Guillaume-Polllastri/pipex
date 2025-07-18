/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:54:05 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/18 11:45:53 by gpollast         ###   ########.fr       */
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

static void	child1(pid_t pid, int *pipefd, char **av)
{
	char	*path;
	char	**cmd;
	int		fd;

	if (pid == 0)
	{
		close(pipefd[0]);
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			exit(1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		path = cmd_path(av[2]);
		cmd = ft_split(av[2], " \t");
		execve(path, cmd, NULL);
		perror("Error\nEnfant 1 Invalid command ");
		exit(EXIT_FAILURE);
	}
}

static void	child2(pid_t pid, int *pipefd, char **av)
{
	char	*path;
	char	**cmd;
	int		fd;

	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		path = cmd_path(av[3]);
		cmd = ft_split(av[3], " \t");
		execve(path, cmd, NULL);
		perror("Error\nEnfant 2 Invalid command ");
		exit(EXIT_FAILURE);
	}
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
		if (pid1 == -1)
		{
			perror("fork");
			return (1);
		}
		child1(pid1, pipefd, av);
		pid2 = fork();
		if (pid2 == -1)
		{
			perror("fork");
			return (1);
		}
		child2(pid2, pipefd, av);
		close(pipefd[1]);
		close(pipefd[0]);
		waitpid(pid1, &status, 0);
		printf("Enfant 1 terminé avec status : %d\n", status);
		waitpid(pid2, &status, 0);
		printf("Enfant 2 terminé avec status : %d\n", status);
		printf("Les deux Enfants ont été crées\n");
		return (0);
	}
	printf("Error\nThe program needs 4 arguments\n");
	return (0);
}
