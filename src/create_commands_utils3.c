/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:52:24 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 11:52:41 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*well_set_command(t_create_command_data	*d,
	t_env_var *vars, int is_wrong)
{
	d->args[d->ind_args] = NULL;
	if (is_wrong)
		d->r = init_command(NULL, NULL, vars);
	else
		d->r = init_command(d->cmd, d->args, vars);
	set_fd(&(d->r), d->fd_in, d->fd_out, 2);
	set_heredoc(&(d->r), d->heredoc);
	return (d->r);
	d->r;
}
