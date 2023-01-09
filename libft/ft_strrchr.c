/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:19:58 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/09 00:40:32 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	offset;

	i = 0;
	offset = -1;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			offset = i;
		}
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	if (offset == -1)
		return (NULL);
	return ((char *)(s + offset));
}
