/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:18:29 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/21 10:57:24 by ratinax          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if (!dst || !src)
		return (0);
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize == 0 || !dst || !src)
		return (src_len);
	if (dest_len > dstsize)
		return (src_len + dstsize);
	while (i < src_len && dest_len + i < dstsize - 1)
	{
		dst[(dest_len) + i] = src[i];
		i++;
	}
	dst[(dest_len) + i] = '\0';
	return (dest_len + src_len);
}
