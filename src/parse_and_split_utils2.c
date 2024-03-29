/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:25:46 by tibernot          #+#    #+#             */
/*   Updated: 2023/02/06 12:00:38 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_to_chr(char *str, char c)
{
	char	*res;
	int		size_str;

	size_str = ft_strlen(str);
	res = ft_calloc(size_str + 1, sizeof(char));
	if (str)
		free(str);
	if (!res)
		return (write(2, "did not malloc\n", 15), NULL);
	res[0] = c;
	return (res);
}

void	rm_heredoc(t_list *lst, int i)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (((char *)tmp->content)[++i])
		{
			if ((((char *)tmp->content)[i] == '<')
				&& (((char *)tmp->content)[i - 1] == '<')
				&& !in_quote(tmp->content, i) && !in_quote(tmp->content, i - 1))
			{
				if (!((char *)tmp->content)[i + 1])
				{
					tmp2 = tmp->next;
					tmp->next = tmp->next->next;
					ft_lstdelone(tmp2, free);
				}
				update_string_hd(tmp, i);
				break ;
			}
		}
		tmp = tmp->next;
	}
}

void	rm_heredocs(t_list **lst)
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	while (lst[i])
	{
		rm_heredoc(lst[i], 0);
		i++;
	}
}

void	update_string_hd(t_list *lst, int i)
{
	t_list	*start;
	t_list	*end;

	end = NULL;
	start = NULL;
	start = get_beggining(lst->content, i, '<');
	end = get_end(lst->content, i);
	if (end)
	{
		end->next = lst->next;
		lst->next = end;
	}
	if (start)
	{
		start->next = lst->next;
		lst->next = start;
		lst->content = str_to_chr(lst->content, 2);
		invert(lst, start);
	}
	else
		lst->content = str_to_chr(lst->content, 2);
}

t_list	**aastr_to_at_list(char ***aastr)
{
	t_list	**blocs;
	int		i;

	i = 0;
	blocs = malloc(sizeof(t_list *) * (ft_aastrlen(aastr) + 1));
	if (!blocs)
		return (write(2, "did not malloc\n", 15), NULL);
	while (aastr[i])
	{
		blocs[i] = astr_to_t_list(aastr[i]);
		if (!blocs[i])
			return (free_alist(blocs), NULL);
		i++;
	}
	blocs[i] = NULL;
	return (blocs);
}
