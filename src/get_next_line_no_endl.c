/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_no_endl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:06:23 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 13:31:59 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_lines(int fd)
{
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		if (tmp)
			res = add_str(res, tmp);
		tmp = get_next_line(fd);
	}
	free(tmp);
	if (!res)
	{
		ft_printf("> \n");
		return (ft_strdup("\0"));
	}
	return (res);
}
