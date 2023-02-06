/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:52:24 by tibernot          #+#    #+#             */
/*   Updated: 2023/02/06 15:25:17 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*well_set_command(t_create_command_data	*d,
	t_env_var *vars, int is_wrong)
{
	d->args[d->ind_args] = NULL;
	if (!d->cmd)
		d->r = init_command(NULL, d->args, vars);
	else
	{
		if (is_wrong)
			d->r = init_command(NULL, d->args, vars);
		else
			d->r = init_command(d->cmd, d->args, vars);
	}
	set_fd(&(d->r), d->fd_in, d->fd_out, 2);
	set_heredoc(&(d->r), d->heredoc);
	return (d->r);
}

int	update_tmp(t_split_alst_on_space_data *d)
{
	free(d->tmp->content);
	if (!d->pre_tmp)
	{
		d->tmp->content = ft_strdup(d->tmp2->content);
		ft_lstdelone(d->tmp2, free);
		if (!d->tmp->content)
			return (0);
	}
	else
		d->tmp = d->tmp2;
	return (1);
}

int	split_alst_on_space(t_list **cmds)
{
	t_split_alst_on_space_data	d;

	d.i = 0;
	d.pre_tmp = NULL;
	while (cmds && cmds[d.i])
	{
		d.tmp = cmds[d.i];
		while (d.tmp)
		{
			if (count_words_not_in_quote(d.tmp->content, ' ') > 1)
			{
				d.tmp2 = split_lst_on_space(&d.tmp, &d.pre_tmp);
				if (!d.tmp2)
					return (0);
				update_tmp(&d);
			}
			d.pre_tmp = d.tmp;
			d.tmp = d.tmp->next;
		}
		d.i++;
	}
	return (1);
}
