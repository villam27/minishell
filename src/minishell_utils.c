/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:28:30 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/26 14:29:36 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in(char c, char *str)
{
	int	i;

	i = 0;
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
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
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
	while (i < index)
	{
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		i++;
	}
	return (is_quote || is_dquote);
}
