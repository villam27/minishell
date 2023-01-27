/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_good_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:20:55 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 12:29:22 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_chars(t_var_to_content_data *d, char *str, int i, int is_gerr)
{
	if (is_gerr)
	{
		d->end = ft_strdup(&str[i + d->j + 1]);
		d->var_name = ft_strdup("?");
		d->start = add_str(d->res, ft_itoa(g_err));
	}
	else
	{
		d->end = ft_strdup(&str[i + d->j]);
		d->var_name = ft_substr(str, i + 1, d->j - 1);
		d->start = add_str(d->res,
				ft_strdup(ft_get_var_content(d->vars, d->var_name)));
	}
}

char	*var_to_content(char *str, int i, t_env_var **vars)
{
	t_var_to_content_data	d;

	d.end = NULL;
	d.start = NULL;
	d.j = 1;
	d.vars = vars;
	if (str[i] == '$'
		&& (!str[i + d.j] || (str[i + d.j] == '$') || str[i + d.j] == '\"'))
		return (str);
	while (i + d.j < (int)ft_strlen(str) && str[i + d. j] != '$'
		&& str[i + d.j] != '?'
		&& str[i + d.j] != '\"' && str[i + d.j] != '\'' && str[i + d.j] != '=')
		d.j++;
	d.res = ft_substr(str, 0, i);
	if (str[i + d.j] && str[i + d.j] == '?')
		init_chars(&d, str, i, 1);
	else
		init_chars(&d, str, i, 0);
	d.res = add_str(d.start, d.end);
	return (free(d.var_name), free(str), str = NULL, d.res);
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

void	to_good_cmds(t_list **cmds, t_env_var **vars)
{
	to_good_args(cmds, vars);
	split_alst_on_space(cmds);
	to_good_tildes(cmds, vars);
	rm_external_quotes(cmds);
}
