/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:55:01 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/21 20:10:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>

typedef struct s_info
{
	char	**arg;
	int		nb_cmd;
	int		last_file;
	int		index_cmd;
}	t_info;

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
	void	(*f)(t_info *);
}	t_child;

char	*cmd_path(char *cmd);
void	parent(t_info *info);
void	create_pipes(t_pipe *pipefd, int nb_cmd);
void	create_processes(t_child *child, t_pipe *pipefd, t_info *info);
void	execute_cmd(t_child *child, t_info *info);
void	free_child(t_child *child);

#endif