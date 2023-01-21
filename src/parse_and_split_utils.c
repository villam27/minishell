/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 14:23:15 by ratinax           #+#    #+#             */
/*   Updated: 2023/01/21 15:04:45 by ratinax          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_aastrlen(char ***astr)
{
	size_t	i;

	i = 0;
	if (!astr)
		return (0);
	while (astr[i])
		i++;
	return (i);
}

size_t	ft_astrlen(char **str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	put_aastring(char ***str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		put_astring(str[i]);
		ft_printf("\n");
		i++;
	}
}

void	free_aastring(char ***str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free_all(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_alist(t_list **alst)
{
	int	i;

	i = 0;
	if (!alst)
		return ;
	while (alst[i])
	{
		ft_lstclear(&alst[i], free);
		i++;
	}
	free(alst);
	alst = NULL;
}
