/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_good_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:20:55 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 11:18:54 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_to_content(char *str, int i, t_env_var **vars)
{
	int		j;
	char	*end;
	char	*var_name;
	char	*res;
	char	*start;

	end = NULL;
	start = NULL;
	j = 1;
	if (str[i] == '$'
		&& (!str[i + j] || (str[i + j] == '$') || str[i + j] == '\"'))
		return (str);
	while (i + j < (int)ft_strlen(str) && str[i + j] != '$'
		&& str[i + j] != '\"' && str[i + j] != '\'' && str[i + j] != '=')
		j++;
	if (str[i + j])
		end = ft_strdup(&str[i + j]);
	var_name = ft_substr(str, i + 1, j - 1);
	res = ft_substr(str, 0, i);
	start = add_str(res, ft_strdup(ft_get_var_content(vars, var_name)));
	res = add_str(start, end);
	free(var_name);
	free(str);
	str = NULL;
	return (res);
}

char	*transform_vars(char *str, t_env_var **vars)
{
	int	i;

	(void) vars;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && !in_squote(str, i))
		{
			if (str[i] == '$' && (!str[i + 1] || str[i + 1] == '$'))
				i++;
			else
			{
				str = var_to_content(str, i, vars);
				if (!str || !str[0])
					return (NULL);
			}
		}
		else
			i++;
	}
	return (str);
}

void	to_good_args(t_list **cmds, t_env_var **vars)
{
	t_list	**tmp;
	t_list	*tmp2;
	int		i;

	i = 0;
	tmp = cmds;
	while (tmp[i])
	{
		tmp2 = tmp[i];
		while (tmp2)
		{
			tmp2->content = transform_vars(tmp2->content, vars);
			tmp2 = tmp2->next;
		}
		i++;
	}
	i = 0;
}

void	split_alst_on_space(t_list **cmds)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*pre_tmp;

	i = 0;
	pre_tmp = NULL;
	while (cmds[i])
	{
		tmp = cmds[i];
		while (tmp)
		{
			if (count_words_not_in_quote(tmp->content, ' ') > 1)
			{
				tmp2 = split_lst_on_space(&tmp, &pre_tmp);
				ft_lstdelone(tmp, free);
				if (!pre_tmp)
					cmds[i] = tmp2;
				tmp = tmp2;
			}
			pre_tmp = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

void	to_good_cmds(t_list **cmds, t_env_var **vars)
{
	to_good_args(cmds, vars);
	split_alst_on_space(cmds);
	to_good_tildes(cmds, vars);
	rm_external_quotes(cmds);
}
