/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:20:53 by alboudje          #+#    #+#             */
/*   Updated: 2022/12/16 11:47:37 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strtoi(const char *str, char *endchar)
{
	long	i;
	long	s;
	int		result;

	i = 0;
	s = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		s *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (result != ((result * 10 + (s * (str[i] - '0'))) / 10))
		{
			errno = 1;
			return ((int)((s + 1) / 2 / -1));
		}
		result = result * 10 + s * (str[i] - '0');
		i++;
	}
	(*endchar) = str[i];
	return ((int)result);
}
