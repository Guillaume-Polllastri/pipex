/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_low.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:06:58 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/19 18:27:31 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_low(unsigned int n)
{
	if (n / 16)
		return (ft_puthex_low((n / 16)) + ft_puthex_low(n % 16));
	else if (!(n / 10))
		ft_putchar_len((char) n + '0');
	else
		ft_putchar_len((char) n - 10 + 'a');
	return (1);
}
