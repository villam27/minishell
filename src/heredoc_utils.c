/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:58:38 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/21 10:59:00 by ratinax          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	while_out(char *str, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (str[i + j] && str[i + j] != ' ')
	{
		if (is_in(str[i + j], "\'\""))
		{
			k = 1;
			while (str[i + j + k] && str[i + j + k] != str[i + j])
				k++;
			j += k;
		}
		else
			j++;
	}
	return (j);
}

int	in_quote(char *str, int index)
{
	int	i;
	int	is_quote;
	int	is_dquote;

	i = 0;
	is_quote = 0;
	is_dquote = 0;
	while (i < index)
	{
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		i++;
	}
	return (is_quote || is_dquote);
}

char	*str_append(char *origin, char *str2, char *str3)
{
	char	*res;

	res = ft_calloc((ft_strlen(origin)
				+ ft_strlen(str2) + ft_strlen(str3) + 1), sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcat(res, origin, ft_strlen(origin) + 1);
	if (str2)
		ft_strlcat(res, (char *)str2, ft_strlen(origin) + ft_strlen(str2) + 1);
	ft_strlcat(res, (char *)str3, ft_strlen(origin)
		+ ft_strlen(str2) + ft_strlen(str3) + 1);
	if (origin)
		free(origin);
	return (res);
}
