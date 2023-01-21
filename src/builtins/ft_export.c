/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:43:05 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/21 19:35:37 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

static t_env_var	*ft_env_new(char *name, char *content)
{
	t_env_var	*result;

	if (!name)
		return (NULL);
	result = malloc(sizeof(t_env_var));
	if (result == NULL)
		return (NULL);
	if (content)
		result->content = ft_strdup(content);
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

	dup_env = ft_env_new(var->name, var->content);
	if (!dup_env)
		return (NULL);
	temp = dup_env;
	while (var->next != NULL)
	{
		var = var->next;
		temp->next = ft_env_new(var->name, var->content);
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

t_env_var	*get_var_addr(char *name, t_env_var **vars)
{
	t_env_var	*temp;

	temp = *vars;
	while (temp)
	{
		if (!ft_strcmp(temp->name, name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

int	add_env(char *name, char *content, t_env_var **vars)
{
	t_env_var	*new;
	t_env_var	*temp;

	new = ft_env_new(name, content);
	if (!new)
		return (1);
	temp = *vars;
	if (temp == NULL)
	{
		*vars = new;
		return (0);
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int	mod_env(char *content, t_env_var **var)
{
	free((*var)->content);
	if (content)
		(*var)->content = ft_strdup(content);
	return (0);
}

int	ft_export(char *name, char *content, t_env_var **vars)
{
	t_env_var *var;

	if (!name && !content)
	{
		ft_print_env(*vars);
		return (1);
	}
	if (!name)
		return (0);
	var = get_var_addr(name, vars);
	if (var)
		mod_env(content, &var);
	else
		add_env(name, content, vars);
	return (0);
}
