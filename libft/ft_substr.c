/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:16:58 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/07 13:02:32 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ns;

	if (len >= (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	ns = (char *) ft_calloc(len + 1, sizeof(char));
	if (!ns)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ns);
	ft_strlcpy(ns, s + start, len + 1);
	return (ns);
}
