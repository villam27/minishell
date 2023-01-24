/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:44:21 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/24 17:20:47 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_lst(t_list	*lst)
{
	while (lst)
	{
		// ft_printf("-%s- ", lst->content);
		ft_printf("-%d- ", ((char *)(lst->content))[0]);
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
