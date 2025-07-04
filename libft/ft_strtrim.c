/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:18:48 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/07 10:09:14 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	find_start(char const *s1, char const *set)
{
	unsigned int		start;

	start = 0;
	while (s1[start])
	{
		if (ft_strchr(set, s1[start]) == NULL)
			return (start);
		start++;
	}
	return (start);
}

static unsigned int	find_end(char const *s1, char const *set,
				unsigned int start)
{
	unsigned int	end;

	end = ft_strlen(s1);
	while (end > start)
	{
		if (ft_strchr(set, s1[end]) == NULL)
			return (end);
		end--;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	char			*res;

	start = find_start(s1, set);
	end = find_end(s1, set, start);
	res = ft_substr(s1, start, end - start + 1);
	return (res);
}
