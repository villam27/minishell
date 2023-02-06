/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:07:01 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/13 18:25:27 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] != c)
			i++;
		else
			return (1);
	}
	return (0);
}

static void	get_word_size(int *start, int *end, char const *s1, char const *set)
{	
	*start = 0;
	while (s1[(*start)] && is_set(s1[(*start)], set))
		(*start)++;
	*end = ft_strlen(s1) - 1;
	while (*end > (*start) && is_set(s1[(*end)], set))
		(*end)--;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	get_word_size(&start, &end, s1, set);
	if (end < start)
		return (ft_strdup(""));
	result = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!result)
		return (write(2, "did not malloc\n", 15), NULL);
	ft_strlcpy(result, s1 + start, end - start + 2);
	return (result);
}
