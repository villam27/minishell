/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:20:16 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 13:08:13 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

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

int	add_env(char *name, char *content, t_env_var **vars, int p_env)
{
	t_env_var	*new;
	t_env_var	*temp;

	if (!name)
		return (1);
	new = ft_env_new(name, content, p_env);
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

int	mod_env(char *content, t_env_var **var, int p_env)
{
	if (p_env)
	{
		free((*var)->content);
		if (content)
			(*var)->content = ft_strdup(content);
		else
			(*var)->content = ft_strdup("");
	}
	if (!(*var)->content)
		return (1);
	return (0);
}

t_env_var	*ft_env_new(char *name, char *content, int p_env)
{
	t_env_var	*result;

	result = malloc(sizeof(t_env_var));
	if (result == NULL)
		return (NULL);
	if (content)
	{
		result->content = ft_strdup(content);
		if (!result->content)
			return (free(result), NULL);
	}
	else if (p_env)
	{
		result->content = ft_strdup("");
		if (!result->content)
			return (free(result), NULL);
	}
	else
		result->content = NULL;
	result->name = ft_strdup(name);
	if (!result->name)
		return (free(result->content), free(result), NULL);
	result->next = NULL;
	return (result);
}

void	ft_sort_env_var(t_env_var **var)
{
	t_env_var	*temp1;
	t_env_var	*temp2;
	char		*name;
	char		*cont;

	temp1 = *var;
	while (temp1)
	{
		temp2 = temp1->next;
		while (temp2)
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
