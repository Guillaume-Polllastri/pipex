/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:08:53 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/16 15:52:23 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*cmd_path(char *cmd)
{
	char	**res;
	char	*path;

	res = ft_split(cmd, " \t");
	if (!res)
		return (NULL);
	path = ft_strjoin("/bin/", res[0]);
	if (!path)
		return (NULL);
	free_string_array(res);
	return (path);
}
