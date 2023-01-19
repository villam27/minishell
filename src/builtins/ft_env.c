/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:10:22 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/19 13:12:28 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	ft_env(t_env_var *vars)
{
	while (vars)
	{
		ft_printf("%s=%s\n", vars->name, vars->content);
		vars = vars->next;
	}
	return (1);
}
