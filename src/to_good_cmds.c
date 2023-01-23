/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_good_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:20:55 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/23 17:41:54 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_good_cmds(t_list **cmds)
{
	t_list	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		tmp = tmp->next;
	}

}
