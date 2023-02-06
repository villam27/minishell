/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:31:33 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 11:52:02 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnlstrcat(char *dest, char *src)
{
	size_t	dl;
	size_t	sl;
	size_t	i;

	if (!src)
		return (NULL);
	dl = ft_strlen(dest);
	sl = ft_strlen(src);
	i = 0;
	while (i < sl && src[i] != '\n')
	{
		dest[(dl) + i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[(dl) + i] = '\n';
		i++;
	}
	dest[(dl) + i] = '\0';
	return (dest);
}

char	*ft_gnlstrjoin(char *s1, char *s2, size_t s2_size)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && ft_strlen(s2) > 0)
		s1 = ft_strdup("");
	if (!s1)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + s2_size + 1));
	if (result == NULL)
	{
		free(s1);
		return (write(2, "did not malloc\n", 15), NULL);
	}
	result[0] = 0;
	ft_gnlstrcat(result, (char *)s1);
	ft_gnlstrcat(result, (char *)s2);
	free(s1);
	return (result);
}
