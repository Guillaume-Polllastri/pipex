/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:54:05 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/16 15:54:45 by gpollast         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		pipefd[2];
	char	*path;
	char	**cmd;

	if (ac == 5)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return (1);
		}
		pid1 = fork();
		if (pid1 == 0)
		{
			printf("PID Enfant 1: %d\n", getpid());
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			path = cmd_path(av[2]);
			cmd = ft_split(av[2], " \t");
			execve(path, cmd, NULL);
			perror("Error\nEnfant 1 Invalid command ");
			return (1);
		}
		waitpid(pid1, &status, 0);
		printf("Enfant 1 terminé\n");
		pid2 = fork();
		if (pid2 == 0)
		{
			printf("PID Enfant 2: %d\n", getpid());
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			path = cmd_path(av[3]);
			cmd = ft_split(av[3], " \t");
			execve(path, cmd, NULL);
			perror("Error\nEnfant 2 Invalid command ");
			return (1);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid2, &status, 0);
		printf("Enfant 2 terminé\n");
		printf("Les deux Enfants ont été crées\n");
		return (0);
	}
	printf("Error\nThe program needs 4 arguments\n");
	// free(path);
	// free_string_array(cmd);
	return (0);
}
