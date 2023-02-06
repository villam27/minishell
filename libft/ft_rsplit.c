/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:20:12 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/29 06:43:49 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_words(char *str, char c)
{
	int	total;
	int	new_word;
	int	i;

	total = 0;
	new_word = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			new_word = 1;
		else if (new_word == 1 && str[i] != c)
		{
			total++;
			new_word = 0;
		}
		i++;
	}
	return (total);
}

static char	*copy_str(char *s, char c, int *start, char r)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] != c && s[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (str == NULL)
		return (write(2, "did not malloc\n", 15), NULL);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = r;
	str[j + 1] = '\0';
	*start += i;
	return (str);
}

char	**ft_rsplit(char const *s, char c, char r)
{
	char	**strs;
	int		j;
	int		start;

	j = 0;
	start = 0;
	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (num_words((char *)s, c) + 1));
	if (strs == NULL)
		return (write(2, "did not malloc\n", 15), NULL);
	while (j < num_words((char *)s, c))
	{
		while (s[start] == c && s[start])
			start++;
		strs[j] = copy_str((char *)s + start, c, &start, r);
		if (strs[j] == NULL)
		{
			free_all(strs);
			return (NULL);
		}
		j++;
	}
	strs[j] = NULL;
	return (strs);
}
