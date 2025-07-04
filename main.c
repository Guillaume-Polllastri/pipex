/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:54:05 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/04 14:59:55 by gpollast         ###   ########.fr       */
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
	pid_t	pid;
	int		status;
	int		fd;

	if (ac == 5)
	{
		fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			return (0);
		write(fd, "rondelle", 8);
		close (fd);
		pid = fork();
		if (pid > 0)
		{
			wait(&status);
			printf("PID Parent: %d\n", pid);
			if (status > 0)
				printf("L'enfant dit que les mots sont differents");
			else
				printf("L'enfant dit que les mots sont identiques");
		}
		else
		{
			printf("PID Enfant: %d\n", pid);
			return (ft_strncmp(av[1], av[2], ft_strlen(av[1])));
		}
	}
	return (0);
}
