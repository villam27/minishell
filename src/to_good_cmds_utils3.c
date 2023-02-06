/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_good_cmds_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:35:14 by tibernot          #+#    #+#             */
/*   Updated: 2023/02/06 15:35:50 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	amount_lst_in_alst(t_list **alst)
{
	t_list	**tmp;
	t_list	*tmp2;
	int		i;
	int		res;

	res = 0;
	i = 0;
	tmp = alst;
	if (!tmp)
		return (0);
	while (tmp[i])
	{
		tmp2 = tmp[i];
		while (tmp2)
		{
			tmp2 = tmp2->next;
			res++;
		}
		i++;
	}
	return (res);
}

int	set_good_args_data(t_list **cmds, t_to_good_args_data *d)
{
	d->i = 0;
	d->j = 0;
	d->tmp = cmds;
	if (!d->tmp)
		return (0);
	d->change_vars = malloc(sizeof(t_list) * amount_lst_in_alst(cmds));
	if (!d->change_vars)
		return (0);
	return (1);
}
