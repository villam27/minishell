/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:58:38 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/19 11:13:58 by ratinax          ###   ########.fr       */
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
		if (is_in(str[i + j], "\'\""))
		{
			k = 1;
			while (str[i + j + k] && str[i + j + k] != str[i + j])
				k++;
			j += k;
		}
		else
			j++;
	}
	return (j);
}

int	in_quote(char *str, int index)
{
	int	i;
	int	is_quote;
	int	is_dquote;

	i = 0;
	is_quote = 0;
	is_dquote = 0;
	while (i < index)
	{
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		i++;
	}
	return (is_quote || is_dquote);
}

static char	*ft_strdup_endl(char *src)
{
	size_t	i;
	char	*str;

	if (!src)
		return (NULL);
	i = ft_strlen(src);
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}

char	**to_astr_endl(t_list **lst)
{
	t_list	*tmp;
	char	**res;
	int		i;

	tmp = *lst;
	i = 0;
	res = malloc(sizeof(char *) * (ft_lstsize(*lst) + 1));
	while (tmp)
	{
		res[i] = ft_strdup_endl((char *) tmp->content);
		i++;
		tmp = tmp->next;
	}
	res[i] = NULL;
	ft_lstclear(lst, free);
	return (res);
}
