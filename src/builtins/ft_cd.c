/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:28:46 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 13:55:07 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include <errno.h>
#include <string.h>

static int	print_errors(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

static int	print_error(char *path)
{
	int	i;

	i = -1;
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

static char	*get_home_path(t_env_var *vars)
{
	while (vars)
	{
		if (!ft_strcmp("HOME", vars->name))
			return (ft_strdup(vars->content));
		vars = vars->next;
	}
	return (NULL);
}

int	ft_cd(char **args, int argc, t_env_var *vars)
{
	char	*path;

	if (argc > 1)
		return (print_errors("too many arguments"));
	if (argc == 0)
		path = get_home_path(vars);
	else
		path = ft_strdup(args[0]);
	if (!path)
		return (print_errors("HOME not set"));
	if (chdir(path) < 0)
	{
		print_error(path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}
