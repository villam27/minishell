/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisignals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:26:31 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 16:52:42 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
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
	//ft_putstr_fd("\n", 2);
}
