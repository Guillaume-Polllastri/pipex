/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 10:55:01 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/22 17:13:26 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>

# define BUFFER_SIZE2 4096

typedef struct s_info
{
	char	**arg;
	int		nb_cmd;
	int		last_file;
	int		index_cmd;
	char	**env;
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

char	*cmd_path(t_info *info, char *cmd);
void	parent(t_info *info);
void	create_pipes(t_pipe *pipefd, int nb_cmd);
void	create_processes(t_child *child, t_pipe *pipefd, t_info *info);
void	execute_cmd(t_child *child, t_info *info);
void	free_child(t_child *child);
void	close_pipes(t_pipe *pipefd, int nb_cmd);
void	wait_children(t_child *children, int nb_cmd);
void	cleanup_children(t_child *children, int nb_cmd);
t_child	*setup_childs(t_info *info);
size_t	ft_strlen_no_nl(const char *str);
char	*my_getenv(t_info *info);
char	*path_env(char *str, char *cmd);

#endif