/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:19:20 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/25 12:11:20 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_str_path(char *str, char *str2)
{
	char	*res;

	res = ft_calloc(sizeof(char) * (ft_strlen(str)
				+ ft_strlen(str2) + 1), sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcat(res, str, ft_strlen(str) + 2);
	ft_strlcat(res, "/", ft_strlen(str) + 3);
	ft_strlcat(res, str2, ft_strlen(str) + ft_strlen(str2) + 2);
	return (res);
}

int	good_cmd(char *str, char *path)
{
	char	**paths;
	int		i;
	char	*test;

	test = NULL;
	i = 0;
	if (access(str, X_OK) == 0)
		return (1);
	paths = ft_split(ft_strnstr(path, "/", ft_strlen(path)), ':');
	while (paths[i])
	{
		test = add_str_path(paths[i], str);
		if (access(test, X_OK) == 0)
			return (free(test), free_all(paths), 1);
		free(test);
		test = NULL;
		i++;
	}
	free_all(paths);
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
	return (0);
}

char	*to_executable_cmd(char *str, char *path)
{
	char	**paths;
	int		i;
	char	*test;

	test = NULL;
	i = 0;
	if (access(str, X_OK) == 0)
		return (ft_strdup(str));
	paths = ft_split(ft_strnstr(path, "/", ft_strlen(path)), ':');
	while (paths[i])
	{
		test = add_str_path(paths[i], str);
		if (access(test, X_OK) == 0)
			return (free_all(paths), test);
		free(test);
		test = NULL;
		i++;
	}
	return (free_all(paths), NULL);
}
