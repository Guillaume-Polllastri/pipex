/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:20:05 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/07 10:09:14 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*ptr_src;
	char		*ptr_dest;
	size_t		i;

	if (!dest && !src)
		return (dest);
	ptr_src = (const char *) src;
	ptr_dest = (char *) dest;
	i = 0;
	if (ptr_dest < ptr_src)
	{
		while (n > 0)
		{
			ptr_dest[i] = ptr_src[i];
			i++;
			n--;
		}
	}
	else
	{
		while (n-- > 0)
			ptr_dest[n] = ptr_src[n];
	}
	return (dest);
}
