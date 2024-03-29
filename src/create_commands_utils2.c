/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:07:46 by tibernot          #+#    #+#             */
/*   Updated: 2023/02/06 14:11:29 by alboudje@st      ###   ########.fr       */
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
	d->fd_in = -15;
	d->fd_out = -15;
	d->tmp = lst;
	d->ind_args = 0;
	d->args = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!d->args)
		write(2, "did not malloc\n", 15);
}

int	amount_fd(t_list **lst)
{
	t_list	**tmp;
	t_list	*tmp2;
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (!lst || !*lst)
		return (0);
	tmp = lst;
	while (tmp && tmp[i])
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
