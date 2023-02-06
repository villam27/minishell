/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:23:08 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 11:58:15 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	if (!content)
		return (NULL);
	result = malloc(sizeof(t_list));
	if (result == NULL)
		return (write(2, "did not malloc\n", 15), free(content), NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}
