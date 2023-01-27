/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:30:24 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/27 13:19:46 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t	check_char(va_list list, char c)
{
	if (c == 'c')
		return ((char)ft_putchar_fd(va_arg(list, int), 1));
	if (c == 'd')
		return (ft_putnbr_fd(va_arg(list, int), 1));
	if (c == 'i')
		return (ft_putnbr_fd(va_arg(list, int), 1));
	if (c == 's')
		return (ft_putstr_fd(va_arg(list, char *), 1));
	if (c == 'u')
		return (ft_uputnbr_fd(va_arg(list, unsigned), 1));
	if (c == 'X')
		return (ft_ullputnbrbase_fd(va_arg(list, unsigned int)
				, "0123456789ABCDEF", 1));
	if (c == 'x')
		return (ft_ullputnbrbase_fd(va_arg(list, unsigned int)
				, "0123456789abcdef", 1));
	if (c == '%')
		return (ft_putchar_fd('%', 1));
	if (c == 'p')
	{
		ft_putstr_fd("0x", 1);
		return (ft_ullputnbrbase_fd(va_arg(list, unsigned long long)
				, "0123456789abcdef", 1) + 2);
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	size_t	i;
	size_t	size_write;

	if (write(1, 0, 0) != 0)
		return (-1);
	va_start(list, str);
	i = 0;
	size_write = 0;
	while (str[i])
	{
		if (str[i] == '%' && ft_strchr("cspdiuxX%", str[i + 1]))
		{
			size_write += check_char(list, str[i + 1]);
			i++;
		}
		else if (str[i] != '%')
			size_write += write(1, &str[i], 1);
		else if (str[i] == '%')
			i++;
		if (str[i] != 0)
			i++;
	}
	va_end(list);
	return (size_write);
}
