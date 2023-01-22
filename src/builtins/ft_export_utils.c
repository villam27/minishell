/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:20:16 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/22 12:22:43 by alboudje         ###   ########.fr       */
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
	return (0);
}
