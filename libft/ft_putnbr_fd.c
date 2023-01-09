/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:29:50 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/21 12:27:11 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

ssize_t	ft_putnbr_fd(int n, int fd)
{
	char	c;
	ssize_t	w_size;

	w_size = 0;
	if (n < 0)
	{
		w_size += ft_putchar_fd('-', fd);
	}
	if (n >= 10 || n <= -10)
		w_size += ft_putnbr_fd(ft_abs(n / 10), fd);
	c = ft_abs(n % 10) + '0';
	return (w_size + ft_putchar_fd(c, fd));
}
