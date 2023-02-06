/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:31:21 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 11:51:16 by alboudje@st      ###   ########.fr       */
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
		return (write(2, "did not malloc\n", 15), NULL);
	ft_bzero(rep, count * size);
	return (rep);
}
