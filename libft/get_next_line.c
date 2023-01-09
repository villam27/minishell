/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 11:31:41 by alboudje          #+#    #+#             */
/*   Updated: 2022/12/19 12:10:33 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_line(char *line, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	j = 0;
	while (buffer[i] != '\n')
		i++;
	result = ft_gnlstrjoin(line, buffer, i + 1);
	if (!result)
	{
		return (NULL);
	}
	while (buffer[i + j])
	{
		buffer[j] = buffer[i + j + 1];
		j++;
	}
	buffer[i + j] = 0;
	return (result);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			read_size;

	read_size = 1;
	line = NULL;
	while (read_size > 0 && BUFFER_SIZE >= 0 && fd >= 0)
	{
		if (ft_strchr(buffer, '\n'))
			return (get_line(line, buffer));
		line = ft_gnlstrjoin(line, buffer, ft_strlen(buffer));
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
		{
			if (line)
				free(line);
			ft_bzero(buffer, BUFFER_SIZE + 1);
			return (NULL);
		}
		buffer[read_size] = 0;
	}
	ft_bzero(buffer, BUFFER_SIZE + 1);
	return (line);
}
