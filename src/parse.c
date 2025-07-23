/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:08:53 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/23 11:05:05 by gpollast         ###   ########.fr       */
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

char	*cmd_path(t_info *info, char *cmd)
{
	char	**res;
	char	*path;

	res = ft_split(cmd, " \t");
	if (!res)
		return (NULL);
	if (cmd[0] == '/')
		path = ft_strdup(res[0]);
	else
		path = path_env(my_getenv(info), res[0]);
	free_string_array(res);
	if (!path)
		return (NULL);
	return (path);
}

size_t	ft_strlen_no_nl(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*my_getenv(t_info *info)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], "PATH=", ft_strlen("PATH=")))
			return (info->env[i]);
		i++;
	}
	return (NULL);
}

char	*path_env(char *str, char *cmd)
{
	char	**path_lst;
	char	*path;
	int		len;
	int		i;

	path_lst = ft_split(str, ":");
	if (!path_lst)
		return (NULL);
	i = -1;
	while (path_lst[++i])
	{
		len = ft_strlen(path_lst[i]) + ft_strlen(cmd) + 2;
		path = malloc(sizeof(char) * len);
		if (!path)
			return (free_string_array(path_lst), NULL);
		ft_bzero(path, len);
		ft_strlcat(path, path_lst[i], len);
		ft_strlcat(path, "/", len);
		ft_strlcat(path, cmd, len);
		if (!access(path, X_OK))
			return (free_string_array(path_lst), path);
		free(path);
	}
	return (free_string_array(path_lst), NULL);
}
