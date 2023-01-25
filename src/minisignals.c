/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisignals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:26:31 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 11:35:52 by alboudje         ###   ########.fr       */
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
