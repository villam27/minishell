/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:58:38 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/12 19:02:25 by tibernot         ###   ########.fr       */
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
