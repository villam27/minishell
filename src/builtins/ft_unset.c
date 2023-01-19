/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:12:06 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/19 12:45:48 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

static int	ft_delone(t_env_var *var)
{
	free(var->name);
	free(var->content);
	free(var);
	var = NULL;
	return (1);
}

int	ft_unset(char *arg, t_env_var **vars)
{
	t_env_var	*temp;
	t_env_var	*prev;

	if (!arg || !(*vars))
		return (0);
	temp = (*vars);
	prev = NULL;
	if (!ft_strcmp(arg, temp->name))
	{
		(*vars) = (*vars)->next;
		ft_delone(temp);
		return (1);
	}
	prev = temp;
	temp = temp->next;
	while (temp)
	{
		if (!ft_strcmp(arg, temp->name))
		{
			prev->next = temp->next;
			ft_delone(temp);
			return (1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}
