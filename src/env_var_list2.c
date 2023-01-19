/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:41:22 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/19 09:36:11 by ratinax          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_var(t_env_var **vars, char *name, char *new_content)
{
	t_env_var	*tmp;

	tmp = *vars;
	while (tmp && ft_strncmp(tmp->name, name, ft_strlen(name)) != 0)
		tmp = tmp->next;
	if (!tmp)
		return ;
	if (tmp->content)
		free(tmp->content);
	tmp->content = new_content;
}

char	*ft_get_var_content(t_env_var **vars, char *name)
{
	t_env_var	*tmp;

	tmp = *vars;
	while (tmp && ft_strncmp(tmp->name, name, ft_strlen(name)) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp->content);
}
