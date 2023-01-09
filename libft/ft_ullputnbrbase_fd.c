/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ullputnbrbase_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:24:47 by alboudje          #+#    #+#             */
/*   Updated: 2022/12/09 21:23:18 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_ullputnbrbase_fd(unsigned long long int n, char *base, int fd)
{
	size_t		size;
	ssize_t		w_size;
	char		c;

	w_size = 0;
	size = ft_strlen(base);
	if (n >= size)
		w_size += ft_ullputnbrbase_fd(n / size, base, fd);
	c = base[n % size];
	return (ft_putchar_fd(c, 1) + w_size);
}
