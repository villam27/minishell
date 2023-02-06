/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:14:54 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 11:51:57 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup("\0"));
	i = start;
	while (s[i] && i < len + start)
		i++;
	result = malloc(sizeof(char) * (i + 1 - start));
	if (!result)
		return (write(2, "did not malloc\n", 15), NULL);
	i = 0;
	while (s[i + start] && i < len)
	{
		result[i] = s[i + start];
		i++;
	}
	result[i] = '\0';
	return (result);
}
