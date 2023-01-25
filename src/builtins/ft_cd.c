/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:28:46 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 16:03:40 by tibernot         ###   ########.fr       */
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

static int	change_pwd(t_env_var *vars, char *path)
{
	while (vars)
	{
		if (!ft_strcmp("PWD", vars->name))
		{
			free(vars->content);
			vars->content = ft_strdup(path);
			if (!vars->content)
				return (1);
			return (0);
		}
		vars = vars->next;
	}
	return (1);
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
	change_pwd(vars, path);
	free(path);
	return (0);
}
