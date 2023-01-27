/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:09:20 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/26 16:31:27 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	convert_lvl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (ft_atoi(str));
}

static void	sh_puterror(int i)
{
	ft_putstr_fd("minishell: warning: shell level (", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
}

static void	sh_full_check(int lvl, t_env_var **v)
{
	t_env_var	*vars;

	vars = *v;
	free(vars->content);
	if (lvl == 1000)
		vars->content = ft_strdup("");
	else if (lvl > 1000)
	{
		sh_puterror(lvl);
		vars->content = ft_strdup("1");
	}
	else
		vars->content = ft_itoa(lvl);
	if (!vars->content)
		exit (1);
}

void	check_shlvl(t_env_var **v)
{
	int			lvl;
	t_env_var	*vars;

	lvl = 0;
	vars = *v;
	while (vars)
	{
		if (!ft_strcmp(vars->name, "SHLVL"))
		{
			lvl = convert_lvl(vars->content);
			sh_full_check(lvl + 1, &vars);
			return ;
		}
		vars = vars->next;
	}
	single_export("SHLVL=1", v);
}
