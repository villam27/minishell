/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_no_endl.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:06:23 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/26 11:13:32 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_lines(int fd)
{
	char	*res;
	char	*tmp;
	int		nb_lines;

	res = NULL;
	tmp = get_next_line(fd);
	nb_lines = ft_atoi(tmp);
	free(tmp);
	tmp = NULL;
	while (nb_lines > 1)
	{
		tmp = get_next_line(fd);
		if (tmp)
			res = add_str(res, tmp);
		tmp = NULL;
		nb_lines--;
	}
	free(tmp);
	return (res);
}
