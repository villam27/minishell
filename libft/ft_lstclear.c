/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:59:03 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/11 14:24:07 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_temp;

	if (!del || !lst)
		return ;
	while (*lst != NULL)
	{
		next_temp = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = next_temp;
	}
}
