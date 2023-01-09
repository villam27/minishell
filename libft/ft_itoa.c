/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:36:41 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/13 13:11:37 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

static char	*ft_strcat(char *dest, char src)
{
	int	dl;

	dl = ft_strlen(dest);
	dest[(dl)] = src;
	dest[(dl) + 1] = '\0';
	return (dest);
}

static int	get_size(int number)
{
	int	size;

	size = 0;
	if (number >= 10 || number < 0)
	{
		size += get_size(ft_abs(number / 10));
	}
	return (size + 1);
}

static void	fill(char *result, int number)
{
	char	c;

	if (number < 0)
	{
		ft_strcat(result, '-');
	}
	if (number >= 10 || number <= -10)
		fill(result, ft_abs(number / 10));
	c = ft_abs(number % 10) + '0';
	ft_strcat(result, c);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*result;
	int		size;

	sign = 0;
	if (n < 0)
		sign = 1;
	size = get_size(n);
	result = (char *)malloc(sizeof(char) * (size + sign + 1));
	if (result == NULL)
		return (NULL);
	result[0] = 0;
	fill(result, n);
	return (result);
}
