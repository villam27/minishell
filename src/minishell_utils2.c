/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:18:45 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/28 14:23:02 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_in(str[i], " \t"))
		i++;
	if (!str[i])
		return (1);
	return (0);
}
