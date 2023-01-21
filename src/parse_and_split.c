/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:30:37 by ratinax           #+#    #+#             */
/*   Updated: 2023/01/21 18:39:31 by ratinax          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_beggining(char	*str, int i)
{
	t_list	*res;

	if (i > 1)
		res = ft_lstnew(ft_substr(str, 0, i - 1));
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

	j = 1;
	if (!str || !str[i + j])
		return (NULL);
	while (str[j + i])
	{
		if (str[j + i] == '<' && str[j + i - 1] == '<'
				&& !in_quote(str, i + j) && i + j > 1)
		{
			res = ft_lstnew(ft_substr(str, j + i - 1,
				ft_strlen(str + j + i - 1)));
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

char	*str_to_1(char *str)
{
	char	*res;
	int		size_str;

	size_str = ft_strlen(str);

	ft_printf("%s\n", str);
	res = ft_calloc(size_str + 1, sizeof(char));
	if (str)
		free(str);
	if (!res)
		return (NULL);
	res[0] = 2;
	return (res);
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

t_list	**aastr_to_at_list(char ***aastr)
{
	t_list	**blocs;
	int		i;

	i = 0;
	blocs = malloc(sizeof(t_list *) * (ft_aastrlen(aastr) + 1));
	if (!blocs)
		return (NULL);
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

void	put_lst(t_list	*lst)
{
	while (lst)
	{
		ft_printf("-%s- ", lst->content);
		lst = lst->next;
	}
	ft_printf("\n");
}

void	put_alst(t_list **alst)
{
	int i;

	i = 0;
	while (alst && *alst && alst[i])
	{
		put_lst(alst[i]);
		i++;
	}
}

void	update_string_hd(t_list *lst, int i)
{
	int		j;
	t_list	*start;
	t_list	*end;

	end = NULL;
	start = NULL;
	j = 0;
	start = get_beggining(lst->content, i);
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
	}
	lst->content = str_to_1(lst->content);
}

void	rm_heredoc(t_list *lst)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		i;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (((char *)tmp->content)[++i])
		{
			if ((((char *)tmp->content)[i] == '<')
				&& (((char *)tmp->content)[i - 1] == '<')
				&& !in_quote(tmp->content, i))
				{
					if (!((char *)tmp->content)[i + 1])
					{
						tmp2 = tmp->next;
						tmp->next = tmp->next->next;
						ft_lstdelone(tmp2, free);
					}
					update_string_hd(tmp, i);
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
		rm_heredoc(lst[i]);
		i++;
	}
}

char	***get_all(char	*line)
{
	char	**blocs;
	char	***res;
	int		i;
	t_list	**alst;

	i = 0;
	blocs = ft_split_not_in_quotes(line, '|');
	if (!blocs)
		return (NULL);
	// ft_printf("%d", ft_astrlen(blocs));
	res = malloc(sizeof(char **) * (ft_astrlen(blocs) + 1));
	if (!res)
		return (free_all(blocs), NULL);
	while (blocs[i])
	{
		res[i] = ft_split_not_in_quotes(blocs[i], ' ');
		i++;
	}
	res[i] = NULL;
	// put_aastring(res);
	alst = aastr_to_at_list(res);
	rm_heredocs(alst);
	if (alst)
		put_alst(alst);
	else
		ft_printf("no alst\n");
	//if (!alst)
	//	return (NULL);

}
