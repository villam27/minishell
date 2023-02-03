/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:10:22 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/30 16:02:49 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../minishell.h"

int	ft_env(t_env_var *vars)
{
	char	*tmp;

	tmp = NULL;
	while (vars)
	{
		if (vars->content)
			tmp = str_without_external_quotes(ft_strdup(vars->content));
		if (tmp)
			ft_printf("%s=%s\n", vars->name, tmp);
		free(tmp);
		tmp = NULL;
		vars = vars->next;
	}
	g_err = 0;
	return (1);
}
