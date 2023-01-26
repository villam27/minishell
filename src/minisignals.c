/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisignals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:26:31 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/26 14:29:50 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	(void)sig;
	ft_printf("exit C\n");
}

void	sigquit_process(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", 2);
	exit(131);
}

void	sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
}
