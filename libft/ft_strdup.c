/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:39:11 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 11:51:40 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*str;

	if (!src)
		return (NULL);
	i = ft_strlen(src);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (write(2, "did not malloc\n", 15), NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
