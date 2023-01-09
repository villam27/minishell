/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:31:21 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/11 14:31:35 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*rep;

	if (size > 0 && count > ULLONG_MAX / size)
		return (NULL);
	rep = malloc(count * size);
	if (rep == NULL)
		return (NULL);
	ft_bzero(rep, count * size);
	return (rep);
}
