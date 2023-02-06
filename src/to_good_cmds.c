/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_good_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:20:55 by tibernot          #+#    #+#             */
/*   Updated: 2023/02/06 15:34:24 by alboudje@st      ###   ########.fr       */
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
		if (ft_get_var_content(d->vars, d->var_name))
			d->start = add_str(d->res,
					ft_strdup(ft_get_var_content(d->vars, d->var_name)));
		else
			d->start = add_str(d->res,
					ft_strdup("\0"));
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

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && !in_squote(str, i))
		{
			if (str[i] == '$' && (!str[i + 1]
					|| str[i + 1] == '$' || str[i + 1] == '\"'))
				i++;
			else
			{
				str = var_to_content(str, i, vars);
				if (!str || !str[0])
					return (free(str), str = NULL, NULL);
			}
		}
		else
			i++;
	}
	return (str);
}

t_list	**to_good_args(t_list **cmds, t_env_var **vars)
{
	t_to_good_args_data	d;

	if (!set_good_args_data(cmds, &d))
		return (NULL);
	while (d.tmp[d.i])
	{
		d.tmp2 = d.tmp[d.i];
		while (d.tmp2)
		{
			d.pre_str = ft_strdup(d.tmp2->content);
			if (!d.pre_str)
				return (free(d.change_vars), NULL);
			d.tmp2->content = transform_vars(d.tmp2->content, vars);
			if (!d.tmp2->content)
				return (free(d.pre_str), free(d.change_vars), NULL);
			if (strcmp(d.pre_str, d.tmp2->content) != 0)
				d.change_vars[d.j++] = d.tmp2;
			free(d.pre_str);
			d.tmp2 = d.tmp2->next;
		}
		d.i++;
	}
	d.change_vars[d.j] = NULL;
	return (d.change_vars);
}

void	to_good_cmds(t_list **cmds, t_env_var **vars)
{
	t_list	**change_vars;

	change_vars = to_good_args(cmds, vars);
	if (!change_vars)
	{
		free_alist(cmds);
		return ;
	}
	to_good_tildes(cmds, vars);
	rm_external_quotes(cmds);
	if (!split_alst_on_space(change_vars))
		free_alist(cmds);
	free(change_vars);
}
