/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guill <guill@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:24:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/19 21:22:12 by guill            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static int	count_number(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		return (1);
	if (n == -2147483648)
	{
		return (11);
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_putnbr(int n)
{
	char	res;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_len('-');
		n *= -1;
	}
	if (n > 9)
		ft_putnbr_len((n / 10));
	res = (n % 10) + '0';
	ft_putchar_len(res);
}

int	ft_putnbr_len(int n)
{
	ft_putnbr(n);
	return (count_number(n));
}
