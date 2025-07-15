/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:54:05 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/15 17:50:01 by gpollast         ###   ########.fr       */
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
	int		fd;
	int		pipefd[2];
	char	*args[3];
	char	*args2[3];

	args[0] = "ls";
	args[1] = "-la";
	args[2] = NULL;
	args2[0] = "wc";
	args2[1] = "-l";
	args2[2] = NULL;
	if (ac == 5)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return (1);
		}
		fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (0);
		write(fd, "rondelle", 8);
		close (fd);
		pid1 = fork();
		if (pid1 > 0)
		{
			printf("PID Enfant 1: %d\n", pid1);
			execve("/bin/ls", args, NULL);
		}
		pid2 = fork();
		if (pid2 > 0)
		{
			printf("PID Enfant 2: %d\n", pid2);
			execve("/bin/wc", args2, NULL);
			return (ft_strncmp(av[1], av[2], ft_strlen(av[1])));
		}
	}
	return (0);
}
