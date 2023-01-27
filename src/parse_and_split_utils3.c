/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:47:50 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/23 15:25:12 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invert(t_list *lst, t_list *lst2)
{
	char	*content;

	content = lst->content;
	lst->content = lst2->content;
	lst2->content = content;
}

void	update_string_fi(t_list *lst, int i, char *str_end, char *str)
{
	t_list	*start;
	t_list	*end;

	end = NULL;
	start = get_beggining(lst->content, i, str[i]);
	if (str_end)
		end = ft_lstnew(ft_strdup(str_end));
	if (end && ((char *)end->content)[0])
	{
		end->next = lst->next;
		lst->next = end;
	}
	else
		ft_lstdelone(end, free);
	if (start)
	{
		start->next = lst->next;
		lst->next = start;
		lst->content = str_to_chr(lst->content, str[i]
				+ (str[i] == str[i + 1]) - 70);
		invert(lst, start);
	}
	else
		lst->content = str_to_chr(lst->content, str[i]
				+ (str[i] == str[i + 1]) - 70);
}

void	replace_file_in(t_list *lst)
{
	t_list	*tmp;
	int		i;

	tmp = lst;
	while (tmp)
	{
		i = -1;
		while (((char *)tmp->content)[++i])
		{
			if (((((char *)tmp->content)[i] == '<')
				|| (((char *)tmp->content)[i] == '>'))
				&& !in_quote(tmp->content, i))
			{
				if (((char *)tmp->content)[i + 1])
					update_string_fi(tmp, i, &((char *)tmp->content)[i + 1
						+ (((char *)tmp->content)[i] == ((char *)tmp->content)[i
							+ 1])], tmp->content);
				else
					update_string_fi(tmp, i, &((char *)tmp->content)[i + 1],
						tmp->content);
				break ;
			}
		}
		tmp = tmp->next;
	}
}

void	replace_file_in_file_outs(t_list **lst)
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	while (lst[i])
	{
		replace_file_in(lst[i]);
		i++;
	}
}
