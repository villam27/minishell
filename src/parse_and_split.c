/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:30:37 by ratinax           #+#    #+#             */
/*   Updated: 2023/01/23 14:13:59 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_beggining(char	*str, int i)
{
	t_list	*res;
	int		j;

	j = 0;
	while (i > 0 && str[i] == '<')
	{
		// ft_printf(":%c:", str[i]);
		i--;
	}
	if (i == 0 && str[i] == '<')
		return (NULL);
	i++;
	while (i > 0)
	{
		j++;
		i--;
	}
	if (j >= 1)
		res = ft_lstnew(ft_substr(str, 0, j));
	else
		return (NULL);
	if (!res)
		return (NULL);
	if (!res->content)
		return (ft_lstclear(&res, free), NULL);
	return (res);
}

t_list	*get_end(char *str, int i)
{
	int		j;
	t_list	*res;

	j = 0;
	if (!str || i >= (int)ft_strlen(str))
		return (NULL);
	while (str[j + i])
	{
		if ((str[i + j] == '<' || str[i + j] == '>') && !in_quote(str, i + j) && j != 0)
		{
			// ft_printf("::%c%c%c::\n", str[i + j + 1], str[i + j], str[i + j - 1]);
			res = ft_lstnew(ft_substr(str, i + j,
				ft_strlen(str)));
			if (!res)
				return (NULL);
			if (!res->content)
				return (ft_lstclear(&res, free), NULL);
			return (res);
		}
		j++;
	}
	return (NULL);
}

t_list	*get_end_hd(char *str, int i)
{
	int		j;
	t_list	*res;

	j = 0;
	if (!str || i >= (int)ft_strlen(str))
		return (NULL);
	while (str[j + i])
	{
		if ((str[i + j] == '<' || str[i + j] == '>') && !in_quote(str, i) && j != 0)
		{
			res = ft_lstnew(ft_substr(str, i + j,
				ft_strlen(str)));
			if (!res)
				return (NULL);
			if (!res->content)
				return (ft_lstclear(&res, free), NULL);
			return (res);
		}
		j++;
	}
	return (NULL);
}

t_list	*astr_to_t_list(char **str)
{
	t_list	*lst;
	int		i;

	if (!str)
		return (NULL);
	i = 1;
	lst = ft_lstnew(str[0]);
	while (str[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(str[i]));
		i++;
	}
	if (ft_lstsize(lst) != i)
		return (ft_lstclear(&lst, free), NULL);
	return (lst);
}

char	***get_all(char	*line, int	*fds)
{
	char	**blocs;
	char	***res;
	int		i;
	t_list	**alst;

	(void) fds;
	i = -1;
	blocs = ft_split_not_in_quotes(line, '|');
	if (!blocs)
		return (NULL);
	res = malloc(sizeof(char **) * (ft_astrlen(blocs) + 1));
	if (!res)
		return (free_all(blocs), NULL);
	while (blocs[++i])
		res[i] = ft_split_not_in_quotes(blocs[i], ' ');
	res[i] = NULL;
	alst = aastr_to_at_list(res);
	rm_heredocs(alst);
	replace_file_in_file_outs(alst);
	if (alst)
		put_alst(alst);
	if (!alst)
		return (NULL);
	return (NULL);
}
