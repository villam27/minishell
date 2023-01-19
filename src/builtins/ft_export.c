/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:43:05 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/19 13:13:38 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

/*
	export VAR 	//do nothing
	export VAR= //create empty
	export 		//print all var in ascii order
*/

static t_env_var	*ft_env_new(char *name, char *content)
{
	t_env_var	*result;

	if (!name)
		return (NULL);
	result = malloc(sizeof(t_env_var));
	if (result == NULL)
		return (NULL);
	result->content = ft_strdup(content);
	result->name = ft_strdup(name);
	result->next = NULL;
	return (result);
}

/*static int	ft_env_size(t_env_var *var)
{
	int	i;

	i = 0;
	while (var != NULL)
	{
		i++;
		var = var->next;
	}
	return (i);
}*/

static void	ft_sort_int_tab(t_env_var **var)
{
	t_env_var	*temp1;
	t_env_var	*temp2;
	char		*name = NULL;
	char		*cont = NULL;

	temp1 = *var;
	temp2 = *var;
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

static t_env_var	*ft_env_dup(t_env_var *var)
{
	t_env_var	*dup_env;
	t_env_var	*temp;
	
	dup_env = ft_env_new(var->name, var->content);
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
	temp = var_dup;
	ft_sort_int_tab(&var_dup);
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

int	ft_export(char *name, char *content, t_env_var **vars)
{
	t_env_var	*new;
	t_env_var	*temp;

	if (!name && !content)
	{
		ft_print_env(NULL);
		return (1);
	}
	if (!name)
		return (0);
	if (ft_strchr(name, '?'))
		return (ft_putstr_fd("minishell: export: `?': not a valid identifier", 2));
	new = ft_env_new(name, content);
	if (!new)
		return (0);
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
