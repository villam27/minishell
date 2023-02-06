/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_good_cmds_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:01:52 by tibernot          #+#    #+#             */
/*   Updated: 2023/02/06 15:37:09 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_squote(char *str, int index)
{
	int	i;
	int	is_dquote;
	int	is_squote;

	i = 0;
	is_dquote = 0;
	is_squote = 0;
	while (i < index)
	{
		is_squote = is_squote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_squote);
		i++;
	}
	return (is_squote);
}

void	to_good_tildes(t_list **cmds, t_env_var **vars)
{
	t_list	**tmp;
	t_list	*tmp2;
	int		i;

	tmp = cmds;
	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		tmp2 = tmp[i];
		while (tmp2)
		{
			if (ft_strcmp(tmp2->content, "~") == 0)
			{
				free (tmp2->content);
				tmp2->content = ft_strdup(ft_get_var_content(vars, "HOME"));
			}
			tmp2 = tmp2->next;
		}
		i++;
	}
}

int	size_without_external_quote(char *str)
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
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		i++;
	}
	return (res);
}

char	*str_without_external_quotes(char *str)
{
	char	*res;
	int		i;
	int		is_quote;
	int		is_dquote;
	int		j;

	i = 0;
	j = 0;
	is_quote = 0;
	is_dquote = 0;
	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (size_without_external_quote(str) + 1));
	if (!res)
		return (write(2, "did not malloc\n", 15), NULL);
	while (str[i])
	{
		if (!((str[i] == '\"' && !is_quote) || (str[i] == '\'' && !is_dquote)))
			res[j++] = str[i];
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		i++;
	}
	res[j] = '\0';
	return (free(str), res);
}

void	rm_external_quotes(t_list **cmds)
{
	t_list	**tmp;
	t_list	*tmp2;
	int		is_export;
	int		i;

	i = 0;
	tmp = cmds;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		is_export = 0;
		tmp2 = tmp[i];
		while (tmp2)
		{
			if (ft_strncmp(tmp2->content, "export", 6) == 0)
				is_export = 1;
			tmp2->content = str_without_external_quotes2(tmp2->content,
					is_export);
			tmp2 = tmp2->next;
		}
		i++;
	}
}
