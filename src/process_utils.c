/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:20:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/23 16:44:54 by gpollast         ###   ########.fr       */
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

void	wait_children(t_child *children, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		waitpid(children[i].pid, &children[i].status, 0);
		i++;
	}
}

void	cleanup_children(t_child *children, int nb_cmd)
{
	int	i;

	i = -1;
	while (++i < nb_cmd)
	{
		free(children[i + 1].path_cmd);
		free_string_array(children[i + 1].cmd);
	}
}

static void	execute_heredoc(t_info *info)
{
	t_list	*lst;
	char	*line;

	lst = NULL;
	line = get_next_line(0);
	if (!line)
		return ;
	while (ft_strncmp(line, info->arg[2], ft_strlen_no_nl(line)) != 0)
	{
		ft_lstadd_back(&lst, ft_lstnew(line));
		line = get_next_line(0);
	}
	while (lst)
	{
		write(1, lst->content, ft_strlen(lst->content));
		lst = lst->next;
	}
	exit(0);
}

static void	execute_read_file(t_info *info)
{
	int		fd;
	char	buffer[BUFFER_SIZE2];
	int		len;

	fd = open(info->arg[1], O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	len = read(fd, buffer, BUFFER_SIZE2);
	while (len > 0)
	{
		write(1, buffer, len);
		len = read(fd, buffer, BUFFER_SIZE2);
	}
	close(fd);
	exit(0);
}

t_child	*setup_childs(t_info *info)
{
	t_child	*children;
	int		i;

	children = malloc(sizeof(t_child) * (info->nb_cmd + 1));
	if (!children)
	{
		perror("Error\nAllocating memory for children\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(children, sizeof(t_child) * (info->nb_cmd + 1));
	if (!ft_strncmp(info->arg[1], "here_doc", ft_strlen(info->arg[1])))
		children[0].f = execute_heredoc;
	else
		children[0].f = execute_read_file;
	i = 0;
	while (i < info->nb_cmd)
	{
		children[i + 1].path_cmd = cmd_path(info,
				info->arg[info->index_cmd + i]);
		children[i + 1].cmd = ft_split(info->arg[info->index_cmd + i], " \t");
		i++;
	}
	return (children);
}
