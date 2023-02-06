/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:58:38 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 13:27:49 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	while_out(char *str, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (str[i + j] && str[i + j] != ' ')
	{
		if ((str[i + j] == '<' || str[i + j] == '>' || str[i + j] == '|')
			&& !in_quote(str, i) && j != 0)
			return (j);
		if (is_in(str[i + j], "\'\""))
		{
			k = 1;
			while (str[i + j + k] && str[i + j + k] != str[i + j])
				k++;
			j += k;
		}
		j++;
	}
	return (j);
}

char	*str_append(char *origin, char *str2, char *str3)
{
	char	*res;

	res = ft_calloc((ft_strlen(origin)
				+ ft_strlen(str2) + ft_strlen(str3) + 1), sizeof(char));
	if (!res)
		return (write(2, "did not malloc\n", 15), NULL);
	ft_strlcat(res, origin, ft_strlen(origin) + 1);
	if (str2)
		ft_strlcat(res, (char *)str2, ft_strlen(origin) + ft_strlen(str2) + 1);
	ft_strlcat(res, (char *)str3, ft_strlen(origin)
		+ ft_strlen(str2) + ft_strlen(str3) + 1);
	if (origin)
		free(origin);
	return (res);
}

int	set_do_heredoc_data(t_do_heredoc_data *d)
{
	d->res = NULL;
	d->line = NULL;
	if (pipe(d->pipes) < 0)
		return (0);
	return (1);
}

int	while_hd(char *hd_out, t_do_heredoc_data *d)
{
	while (ft_strcmp(hd_out, d->line) != 0)
	{
		d->line = new_readline(d->line, "> ");
		d->nb_lines++;
		if (!d->line)
			return (1);
		else if (ft_strcmp(hd_out, d->line) != 0)
			d->res = str_append(d->res, d->line, "\n");
	}
	return (1);
}
