/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:43:05 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/23 15:54:11 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

t_env_var	*ft_env_new(char *name, char *content, int p_env)
{
	t_env_var	*result;

	if (!name)
		return (NULL);
	result = malloc(sizeof(t_env_var));
	if (result == NULL)
		return (NULL);
	if (content)
		result->content = ft_strdup(content);
	else if (p_env)
		result->content = ft_strdup("");
	else
		result->content = NULL;
	result->name = ft_strdup(name);
	if (!result->name)
		return (free(result->content), free(result), NULL);
	result->next = NULL;
	return (result);
}

static void	ft_sort_env_var(t_env_var **var)
{
	t_env_var	*temp1;
	t_env_var	*temp2;
	char		*name;
	char		*cont;

	temp1 = *var;
	while (temp1->next)
	{
		temp2 = temp1->next;
		while (temp2->next)
		{
			if (ft_strcmp(temp1->name, temp2->name) > 0)
			{
				name = temp1->name;
				temp1->name = temp2->name;
				temp2->name = name;
				cont = temp1->content;
				temp1->content = temp2->content;
				temp2->content = cont;
			}
			temp2 = temp2->next;
		}
		temp2 = *var;
		temp1 = temp1->next;
	}
}

/*
	TODO: clear list if malloc broke while looping
*/
static t_env_var	*ft_env_dup(t_env_var *var)
{
	t_env_var	*dup_env;
	t_env_var	*temp;

	dup_env = ft_env_new(var->name, var->content, 1);
	if (!dup_env)
		return (NULL);
	temp = dup_env;
	while (var->next != NULL)
	{
		var = var->next;
		temp->next = ft_env_new(var->name, var->content, 1);
		temp = temp->next;
	}
	return (dup_env);
}

void	ft_print_env(t_env_var *var)
{
	t_env_var	*var_dup;
	t_env_var	*temp;

	var_dup = ft_env_dup(var);
	if (!var_dup)
		return ;
	temp = var_dup;
	ft_sort_env_var(&var_dup);
	while (var_dup != NULL)
	{
		ft_printf("declare -x %s=\"%s\"\n", var_dup->name, var_dup->content);
		var_dup = var_dup->next;
	}
	while (temp)
	{
		ft_unset(temp->name, &temp);
	}
}

/*
	TODO: Check if the var contains a '?' return an error
*/
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
			ft_putstr_fd("Error\n", 2);
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
			result[0] = ft_strdup(value);
			result[1] = NULL;
		}
		else
			return (NULL);
	}
	else
		result = get_result(value);
	return (result);
}

int	ft_export(char *value, t_env_var **vars)
{
	t_env_var	*var;
	char		**variable;
	int			p_env;

	if (!value)
	{
		ft_print_env(*vars);
		return (1);
	}
	p_env = 0;
	if (ft_strchr(value, '='))
		p_env = 1;
	variable = split_args(value);
	if (!variable)
		return (0);
	var = get_var_addr(variable[0], vars);
	if (var)
		mod_env(variable[1], &var, p_env);
	else
		add_env(variable[0], variable[1], vars, p_env);
	free_all(variable);
	return (0);
}
