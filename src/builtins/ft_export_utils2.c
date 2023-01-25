/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:25:46 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 16:04:41 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

t_env_var	*ft_env_dup(t_env_var *var)
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
		if (!temp->next)
		{
			while (dup_env)
				ft_unset_single(dup_env->name, &dup_env);
			return (NULL);
		}
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
		ft_unset(&temp->name, &temp);
	}
}

void	print_var_error(char *func, char *var_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(var_name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
