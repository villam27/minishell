/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_not_in_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:27:15 by ratinax           #+#    #+#             */
/*   Updated: 2023/01/23 15:09:47 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words_not_in_quote(char *s, char c)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] && s[i] != c)
		{
			result++;
			while (s[i] && (s[i] != c || in_quote(s, i)))
				i++;
		}
	}
	return (result);
}

unsigned int	start_word(char *s, char c, int ind)
{
	unsigned int	i;

	i = 0;
	while (s[i] == c)
		i++;
	if (ind == 0)
		return (i);
	while (s[i])
	{
		if (s[i] == c && !in_quote(s, i))
		{
			ind--;
			while (s[i] == c)
				i++;
		}
		if (ind == 0)
			return (i);
		i++;
	}
	return (-1);
}

size_t	size_word(char *s, char c, int ind)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] == c && !in_quote(s, i))
		{
			ind--;
			while (s[i] == c)
				i++;
		}
		while (s[i] && (s[i] != c || in_quote(s, i)) && ind == 0)
		{
			i++;
			j++;
		}
		if (ind == 0)
			return (j);
		i++;
	}
	return (i);
}

void	free_array(char **astring, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(astring[i]);
		i++;
	}
	free(astring);
}

char	**ft_split_not_in_quotes(char *s, char c)
{
	char	**astring;
	int		nb_words;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	nb_words = count_words_not_in_quote(s, c);
	astring = malloc(sizeof(char *) * (nb_words + 1));
	if (!astring)
		return (NULL);
	while (i < nb_words)
	{
		astring[i] = ft_substr(s, start_word(s, c, i), size_word(s, c, i));
		if (!astring[i])
		{
			free_array(astring, i + 1);
			return (NULL);
		}
		i++;
	}
	astring[i] = NULL;
	return (astring);
}
