/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:25:19 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/28 11:19:33 by tibernot         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

static int	put_exit_error(char *str)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_err = 255;
	return (255);
}

u_int8_t	ft_atoc(char *str)
{
	long	i;
	long	s;
	long	result;

	i = 0;
	s = 1;
	result = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		s *= -1;
	else if ((str[i] == '+') || (str[i] == '-'))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result != ((result * 10 + (s * (str[i] - '0'))) / 10))
			return (put_exit_error(str));
		result = result * 10 + s * (str[i] - '0');
		i++;
	}
	if (str[i] != 0)
		return (put_exit_error(str));
	g_err = (int)(u_int8_t)result;
	return ((u_int8_t)result);
}

int	ft_exit(char **args, int argc, t_env_var **vars)
{
	while (*vars)
		ft_unset_single((*vars)->name, vars);
	if (!args[0])
		exit(g_err);
	else if (argc > 1)
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
	exit ((int)ft_atoc(args[0]));
	return (0);
}
