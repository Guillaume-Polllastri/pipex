/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:54:05 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/21 20:42:30 by gpollast         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_info	*info;

	if (ac >= 5)
	{
		info = malloc(sizeof(t_info));
		if (!info)
			return (0);
		info->arg = av;
		info->last_file = ac - 1;
		info->env = env;
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
		parent(info);
		free(info);
		return (0);
	}
	ft_printf("Error\nThe program has not enough arguments\n");
	return (0);
}
