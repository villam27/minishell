/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:43:05 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 14:27:38 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	is_valid(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
		{
			print_var_error("export", name);
			return (1);
		}
	}
	return (0);
}

char	**get_result(char *value)
{
	char	**sp;

	sp = ft_split(value, '=');
	if (!sp)
		return (NULL);
	if (!is_valid(sp[0]))
	{
		if (sp[1])
		{
			free(sp[1]);
			sp[1] = ft_strdup(ft_strrchr(value, '=') + 1);
			if (!sp[1])
				return (free_all(sp), NULL);
		}
	}
	else
		return (free_all(sp), NULL);
	return (sp);
}

char	**split_args(char *value)
{
	int		i;
	char	**result;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	if (!value[i])
	{
		if (!is_valid(value))
		{
			result = malloc(sizeof(char *) * 3);
			if (!result)
				return (NULL);
			result[0] = ft_strdup(value);
			if (!result[0])
				return (free(result), NULL);
			result[1] = NULL;
		}
		else
			return (NULL);
	}
	else
		result = get_result(value);
	return (result);
}

int	single_export(char *value, t_env_var **vars)
{
	t_env_var	*var;
	char		**variable;
	int			p_env;

	p_env = 0;
	if (ft_strchr(value, '='))
		p_env = 1;
	variable = split_args(value);
	if (!variable)
		return (1);
	var = get_var_addr(variable[0], vars);
	if (var)
		mod_env(variable[1], &var, p_env);
	else
		add_env(variable[0], variable[1], vars, p_env);
	free_all(variable);
	return (0);
}

int	ft_export(char **value, t_env_var **vars)
{
	int	i;

	i = 0;
	if (!value[0])
	{
		ft_print_env(*vars);
		return (0);
	}
	while (value[i])
	{
		if (single_export(value[i], vars))
			return (1);
		i++;
	}
	return (0);
}
