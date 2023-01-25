/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:07:48 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 12:14:51 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	check_nl(char **argv, int *i)
{
	int	is_arg;
	int	j;
	int	nl;

	is_arg = 1;
	nl = 1;
	while (is_arg && argv[*i])
	{
		j = 1;
		if (argv[*i][0] != '-')
			break ;
		while (argv[*i][j] == 'n')
			j++;
		if (argv[*i][j] != 0)
			is_arg = 0;
		else
		{
			nl = 0;
			(*i)++;
		}
	}
	return (nl);
}

int	ft_echo(char **argv, int argc)
{
	int	new_line;
	int	i;

	i = 0;
	new_line = check_nl(argv, &i);
	while (i < argc - 1)
	{
		ft_printf("%s", argv[i]);
		ft_printf(" ");
		i++;
	}
	if (argv[i])
		ft_printf("%s", argv[i]);
	if (new_line)
		ft_printf("\n");
	return (1);
}
