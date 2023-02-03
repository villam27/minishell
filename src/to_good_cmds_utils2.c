/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_good_cmds_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:50:53 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/30 17:19:55 by tibernot         ###   ########.fr       */
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

void	pass_equal(char *str, int *i, char *str2, int *j)
{
	if (!str[*i] || str[*i] != '=' || in_quote(str, *i))
		return ;
	(*i)++;
	while (str[*i])
	{
		if (str2 && j)
			str2[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
	if (str2 && j)
		str2[*j] = '\0';
}

int	size_without_external_quote2(char *str)
{
	int	i;
	int	is_quote;
	int	is_dquote;
	int	res;

	i = 0;
	is_quote = 0;
	is_dquote = 0;
	res = 0;
	while (str[i])
	{
		if ((str[i] == '\"' && !is_quote)
			|| (str[i] == '\'' && !is_dquote))
			;
		else
			res++;
		pass_equal(str, &i, NULL, &res);
		if (i >= (int)ft_strlen(str))
			return (res);
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		i++;
	}
	return (res);
}

char	*str_without_external_quotes2(char *str, int is_an_export)
{
	char	*res;
	int		i;
	int		is_quote;
	int		is_dquote;
	int		j;

	(void) is_an_export;
	(void) i;
	(void) j;
	(void) is_quote;
	(void) is_dquote;
	i = 0;
	j = 0;
	is_quote = 0;
	is_dquote = 0;
	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (size_without_external_quote2(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (!((str[i] == '\"' && !is_quote) || (str[i] == '\'' && !is_dquote)))
			res[j++] = str[i];
		if (is_an_export)
			pass_equal(str, &i, res, &j);
		if (i >= (int)ft_strlen(str))
			return (free(str), res);
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		i++;
	}
	res[j] = '\0';
	return (free(str), res);
}
