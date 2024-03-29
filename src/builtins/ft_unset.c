/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:12:06 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/30 17:02:21 by tibernot         ###   ########.fr       */
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

int	ft_unset_single(char *arg, t_env_var **vars)
{
	t_env_var	*temp;
	t_env_var	*prev;

	if (!arg || !(*vars))
		return (0);
	temp = (*vars);
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
			return (ft_delone(temp));
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}

int	ft_unset(char **args, t_env_var **vars)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "unset") && !is_valid(args[i], "unset"))
			ft_unset_single(args[i], vars);
		i++;
	}
	g_err = 0;
	return (0);
}
