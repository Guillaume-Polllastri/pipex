/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 23:19:40 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/07 10:09:14 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*ptr_src;
	char		*ptr_dest;

	ptr_src = (const char *) src;
	ptr_dest = (char *) dest;
	if (!dest && !src)
		return (dest);
	while (n > 0)
	{
		*ptr_dest = *ptr_src;
		ptr_src++;
		ptr_dest++;
		n--;
	}
	return (dest);
}
