/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:07:46 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/26 10:06:56 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_int(int lst, int a, int b, int c)
{
	return ((lst == a) || (lst == b) || (lst == c));
}

int	amount_fd_in_bloc(t_list *lst)
{
	t_list	*tmp;
	int		res;

	res = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->content)
		{
			if (is_in_int(((char *)tmp->content)[0], -7, -8, -10))
				res++;
		}
		tmp = tmp->next;
	}
	return (res);
}

int	amount_hd_in_bloc(t_list *lst)
{
	t_list	*tmp;
	int		res;

	res = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->content)
		{
			if (((char *)tmp->content)[0] == 2)
				res++;
		}
		tmp = tmp->next;
	}
	return (res);
}

void	set_create_command_data(t_create_command_data *d, t_list *lst)
{
	d->pre_is_fd = 0;
	d->cmd = NULL;
	d->heredoc = NULL;
	d->fd_in = -2;
	d->fd_out = -2;
	d->tmp = lst;
	d->ind_args = 0;
	d->args = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
}

int	amount_fd(t_list **lst)
{
	t_list	**tmp;
	t_list	*tmp2;
	int		i;
	int		res;

	i = 0;
	res = 0;
	tmp = lst;
	while (tmp[i])
	{
		tmp2 = tmp[i];
		while (tmp2)
		{
			if (tmp2->content)
				res += ((((char *)(tmp2->content))[0] == -7)
						|| (((char *)(tmp2->content))[0] == -10)
						|| (((char *)(tmp2->content))[0] == -8));
			tmp2 = tmp2->next;
		}
		i++;
	}
	return (res);
}
