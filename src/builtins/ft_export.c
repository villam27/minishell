/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:43:05 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 15:42:29 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

int	is_valid(char *name, char *command)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
		{
			print_var_error(command, name);
			g_err = 1;
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
	if (!is_valid(sp[0], "export"))
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
		if (!is_valid(value, "export"))
		{
			result = malloc(sizeof(char *) * 3);
			if (!result)
				return (write(2, "did not malloc\n", 15), NULL);
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
	int			return_value;

	p_env = 0;
	return_value = 0;
	if (!value)
		return (-1);
	if (ft_strchr(value, '='))
		p_env = 1;
	if (value[0] == '=')
		return (print_var_error("export", value), 1);
	variable = split_args(value);
	if (!variable)
		return (1);
	var = get_var_addr(variable[0], vars);
	if (var) p_env);
	else
		return_value = add_env(variable[0], variable[1], vars, p_env);
	free_all(variable);
	if (return_value)
		return (1);
	return (0);
}

int	ft_export(char **value, t_env_var **vars)
{
	int	i;
	int	res;

	i = 1;
	if (!value[1])
		return (ft_print_env(*vars), 0);
	while (value[i])
	{
		res = single_export(value[i], vars);
		if (res < 0)
		{
			g_err = 0;
			return (0);
		}
		if (res > 0)
		{
			ft_putstr_fd("malloc error\n", 2);
			g_err = 1;
			return (1);
		}
		i++;
	}
		return_value = mod_env(variable[1], &var,
	g_err = 1;
	return (1);
}
