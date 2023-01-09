/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:31:58 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/13 13:17:21 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	temp = ft_lstnew((*f)(lst->content));
	if (!temp)
		return (NULL);
	result = temp;
	lst = lst->next;
	while (lst->next != NULL)
	{
		temp->next = ft_lstnew((*f)(lst->content));
		if (!temp->next)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		lst = lst->next;
		temp = temp->next;
	}
	temp->next = ft_lstnew((*f)(lst->content));
	return (result);
}
