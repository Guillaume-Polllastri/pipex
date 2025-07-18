/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:55:01 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/18 19:10:07 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipe
{
	int	fd[2];
}	t_pipe;

typedef struct s_child
{
	int		in;
	int		out;
	int		status;
	char	*path_cmd;
	char	**cmd;
	pid_t	pid;
}	t_child;

char	*cmd_path(char *cmd);

#endif