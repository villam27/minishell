/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:20:12 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/24 15:32:35 by tibernot         ###   ########.fr       */
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

static char	*copy_str(char *s, char c, int *start)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] != c && s[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	while (j < i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	*start += i;
	return (str);
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

char	**ft_split(char const *s, char c)
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
		return (NULL);
	while (j < num_words((char *)s, c))
	{
		while (s[start] == c && s[start])
			start++;
		strs[j] = copy_str((char *)s + start, c, &start);
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
