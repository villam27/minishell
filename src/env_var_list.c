/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:41:22 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/12 19:02:47 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*ft_env_var_lst_new(char *name, char *content)
{
	t_env_var	*result;

	if (!name)
		return (NULL);
	result = malloc(sizeof(t_env_var));
	if (result == NULL)
		return (NULL);
	result->content = content;
	result->name = name;
	result->next = NULL;
	return (result);
}

void	ft_lst_env_var_add_back(t_env_var **vars, t_env_var *new)
{
	t_env_var	*temp;

	if (!new)
		return ;
	temp = *vars;
	if (temp == NULL)
	{
		*vars = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	ft_env_var_lst_clear(t_env_var **vars, void (*del)(void*))
{
	t_env_var	*next_temp;

	if (!del || !vars)
		return ;
	while (*vars != NULL)
	{
		next_temp = (*vars)->next;
		(*del)((*vars)->content);
		(*del)((*vars)->name);
		free(*vars);
		*vars = next_temp;
	}
}
