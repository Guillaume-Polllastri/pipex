/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:08:34 by gpollast          #+#    #+#             */
/*   Updated: 2025/05/19 18:27:19 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_up(unsigned int n)
{
	if (n / 16)
		return (ft_puthex_up((n / 16)) + ft_puthex_up(n % 16));
	else if (!(n / 10))
		ft_putchar_len((char) n + '0');
	else
		ft_putchar_len((char) n - 10 + 'A');
	return (1);
}
