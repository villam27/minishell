/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:08:27 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/10 14:29:40 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_in(char c, char *str)
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

static int	while_quote(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (!str[*i])
		return (0);
	return (1);
}

static int	while_dquote(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	if (!str[*i])
		return (0);
	return (1);
}

int	parsing_errors(char *str)
{
	int	i;
	int	is_pipe;
	int	is_chev;

	i = 0;
	is_chev = 0;
	is_pipe = 0;
	while (str[i])
	{
		if (is_in(str[i], "< \n\t\v\r"))
			is_chev++;
		else
			is_chev = 0;
		if (is_chev > 2)
			return (1);
		if (is_in(str[i], "| \n\t\v\r"))
			is_pipe++;
		else
			is_pipe = 0;
		if (is_pipe > 1)
			return (1);
		if (str[i] == '\'')
			if (!while_quote(str, &i))
				return (1);
		if (str[i] == '\"')
			if (!while_dquote(str, &i))
				return (1);
		i++;
	}
	if (is_pipe)
		return (1);
	return (0);
}
