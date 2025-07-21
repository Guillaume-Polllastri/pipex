/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:24:58 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/19 18:35:43 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6), 6);
	while (str[i])
	{
		ft_putchar_len(str[i]);
		i++;
	}
	return (i);
}
