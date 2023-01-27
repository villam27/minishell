/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:51:37 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/26 14:41:20 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_vars_size(t_env_var *vars)
{
	int			i;
	t_env_var	*temp;

	i = 0;
	temp = vars;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

static char	*get_str_env(t_env_var *var)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(var->name, "=");
	if (!temp)
		return (NULL);
	temp2 = ft_strjoin(temp, var->content);
	if (!temp2)
		return (free(temp), NULL);
	free(temp);
	return (temp2);
}

char	**get_envp(t_env_var *vars)
{
	char		**envp;
	int			i;
	int			size;
	t_env_var	*temp;

	i = 0;
	size = get_vars_size(vars);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	temp = vars;
	while (i < size)
	{
		envp[i] = get_str_env(temp);
		if (!envp[i])
			free_all(envp);
		temp = temp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
