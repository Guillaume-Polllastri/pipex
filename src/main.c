/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:54:05 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/22 23:56:46 by gpollast         ###   ########.fr       */
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

static int	check_file_permissions(char **av, int ac)
{
	if (!access(av[ac - 1], F_OK) && access(av[ac - 1], W_OK | R_OK))
		return (write(2, "Error\nNo permissions on file2\n", 30), 1);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
	{
		if (access(av[1], F_OK))
			return (write(2, "Error\nThe first file doesn't exist\n", 35), 1);
		if (access(av[1], W_OK | R_OK))
			return (write(2, "Error\nNo permissions on file1\n", 30), 1);
	}
	return (0);
}

static void	setup_info_params(t_info *info, char **av, int ac)
{
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) && ac >= 6)
	{
		info->nb_cmd = ac - 4;
		info->index_cmd = 3;
	}
	else
	{
		info->nb_cmd = ac - 3;
		info->index_cmd = 2;
	}
}

int	main(int ac, char **av, char **env)
{
	t_info	*info;

	if (ac < 5)
		return (ft_printf("Error\nThe program has not enough arguments\n"), 0);
	info = malloc(sizeof(t_info));
	if (!info)
		return (0);
	info->arg = av;
	info->last_file = ac - 1;
	info->env = env;
	if (check_file_permissions(av, ac))
		return (free(info), 0);
	setup_info_params(info, av, ac);
	parent(info);
	free(info);
	return (0);
}
