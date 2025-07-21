/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:04:03 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/19 18:30:04 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex(const unsigned long n)
{
	if (n / 16)
		return (ft_puthex((n / 16)) + ft_puthex(n % 16));
	else if (!(n / 10))
		ft_putchar_len((char) n + '0');
	else
		ft_putchar_len((char) n - 10 + 'a');
	return (1);
}

int	ft_putadress(void *ptr)
{
	if (!ptr)
		return (ft_putstr_len("(nil)"));
	ft_putstr_len("0x");
	return (2 + ft_puthex((unsigned long) ptr));
}
