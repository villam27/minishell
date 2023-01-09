/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:29:50 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/21 12:27:30 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_uputnbr_fd(unsigned int n, int fd)
{
	char	c;
	ssize_t	w_size;

	w_size = 0;
	if (n >= 10)
		w_size += ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	return (ft_putchar_fd(c, fd) + w_size);
}
