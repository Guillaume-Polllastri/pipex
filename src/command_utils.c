/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:45:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/23 16:45:51 by gpollast         ###   ########.fr       */
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

void	setup_redirections(t_child *child)
{
	if (child->in >= 0)
	{
		dup2(child->in, STDIN_FILENO);
		close(child->in);
	}
	if (child->out >= 0)
	{
		dup2(child->out, STDOUT_FILENO);
		close(child->out);
	}
}

void	exec_command(t_child *child, t_info *info)
{
	if (child->path_cmd)
	{
		execve(child->path_cmd, child->cmd, info->env);
		free(child->path_cmd);
		free_string_array(child->cmd);
		perror("Error\nCommand execution failed");
		exit(EXIT_FAILURE);
	}
	else if (child->f)
		child->f(info);
	else
	{
		perror("Error\nCommand is invalid");
		exit(127);
	}
}
