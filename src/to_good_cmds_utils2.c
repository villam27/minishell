/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_good_cmds_tuils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:50:53 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 10:51:06 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*split_lst_on_space(t_list **lst, t_list **pre_lst)
{
	char	**res;
	int		i;
	t_list	*tmp;

	res = ft_split_not_in_quotes((*lst)->content, ' ');
	if (!res)
		return (NULL);
	i = ft_astrlen(res) - 1;
	while (i > 0)
	{
		tmp = ft_lstnew(ft_strdup(res[i]));
		tmp->next = (*lst)->next;
		(*lst)->next = tmp;
		i--;
	}
	tmp = ft_lstnew(ft_strdup(res[0]));
	free_all(res);
	if (pre_lst && (*pre_lst))
		(*pre_lst)->next = tmp;
	tmp->next = (*lst)->next;
	return (tmp);
}
