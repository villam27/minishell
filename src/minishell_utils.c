/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:28:30 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 11:13:35 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char c, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	put_astring(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
	{
		ft_printf("-%s-\n", str[i]);
		i++;
	}
}

char	*new_readline(char *prev_line, char *str)
{
	char	*res;

	free(prev_line);
	res = readline(str);
	return (res);
}

int	in_quote(char *str, int index)
{
	int	i;
	int	is_quote;
	int	is_dquote;

	i = 0;
	is_quote = 0;
	is_dquote = 0;
	if (!str)
		return (0);
	while (i < index)
	{
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		i++;
	}
	return (is_quote || is_dquote);
}

char	*add_str(char *str, char *str2)
{
	char	*res;

	if (!str && !str2)
		return (NULL);
	res = ft_calloc(sizeof(char) * (ft_strlen(str)
				+ ft_strlen(str2) + 1), sizeof(char));
	if (!res)
		return (free(str), free(str2), write(2, "did not malloc\n", 15), NULL);
	ft_strlcat(res, str, ft_strlen(str) + 1);
	ft_strlcat(res, str2, ft_strlen(str) + ft_strlen(str2) + 1);
	free(str);
	free(str2);
	return (res);
}
