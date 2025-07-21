/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putUnbr_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:45:14 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/19 16:13:52 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	count_number(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_putnbr(unsigned int n)
{
	char	res;

	if (n > 9)
		ft_putnbr_len((n / 10));
	res = (n % 10) + '0';
	ft_putchar_len(res);
}

int	ft_putunbr_len(unsigned int n)
{
	ft_putnbr(n);
	return (count_number(n));
}
