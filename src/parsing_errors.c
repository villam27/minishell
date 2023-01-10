/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:08:27 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/10 17:56:08 by tibernot         ###   ########.fr       */
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

static int	two_good(int a, int b, int c)
{
	if (a && b)
		return (1);
	if (a && c)
		return (1);
	if (b && c)
		return (1);
	return (0);
}

int	parsing_errors(char *str)
{
	int	i;
	int	pipe;
	int	chev;
	int	bchev;

	i = 0;
	chev = 0;
	bchev = 0;
	pipe = 0;
	while (str[i])
	{
		chev = (chev + is_in(str[i], "< \n\t")) * is_in(str[i], "< \n\t");
		bchev = (chev + is_in(str[i], "> \n\t")) * is_in(str[i], "> \n\t");
		pipe = (pipe + is_in(str[i], "| \n\t")) * is_in(str[i], "| \n\t");
		if (chev > 2 || pipe > 1 || bchev > 2 || two_good(chev, pipe, bchev))
			return (1);
		if (str[i] == '\'')
			if (!while_quote(str, &i))
				return (1);
		if (str[i] == '\"')
			if (!while_dquote(str, &i))
				return (1);
		i++;
	}
	return (pipe || chev || bchev);
}
