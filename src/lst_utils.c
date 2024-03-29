/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:44:21 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/25 13:04:45 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_lst(t_list	*lst)
{
	while (lst)
	{
		ft_printf("-%s- ", lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
}

void	put_alst(t_list **alst)
{
	int	i;

	i = 0;
	while (alst && *alst && alst[i])
	{
		put_lst(alst[i]);
		i++;
	}
}
