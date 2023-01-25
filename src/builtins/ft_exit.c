/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:25:19 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 09:53:15 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

static int	put_exit_error(char *str)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (255);
}

u_int8_t	ft_atoc(char *str)
{
	size_t		i;
	u_int8_t	result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != 0)
		return (put_exit_error(str));
	return (result);
}

int	ft_exit(char **args, int argc, t_env_var **vars)
{
	while (*vars)
		ft_unset_single((*vars)->name, vars);
	if (!args[0])
		exit(0);
	else if (argc > 1)
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
	exit ((int)ft_atoc(args[0]));
	return (0);
}
