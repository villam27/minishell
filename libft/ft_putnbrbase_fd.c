/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:22:36 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/21 12:27:16 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

ssize_t	ft_putnbrbase_fd(int n, char *base, int fd)
{
	int		i;
	int		size;
	ssize_t	w_size;
	char	c;

	i = 0;
	w_size = 0;
	size = ft_strlen(base);
	if (n < 0)
	{
		write(1, "-", 1);
	}
	if (n >= size - i || n <= -size)
		w_size += ft_putnbrbase_fd(ft_abs(n / size), base, fd);
	c = base[ft_abs(n % size)];
	return (w_size + ft_putchar_fd(c, 1));
}
