/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:30:37 by ratinax           #+#    #+#             */
/*   Updated: 2023/01/21 11:55:40 by ratinax          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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



char	***get_all(char	*line)
{
	char	**blocs;
	char	***res;
	int		i;

	i = 0;
	blocs = ft_split_not_in_quotes(line, '|');
	if (!blocs)
		return (NULL);
	// ft_printf("%d", ft_astrlen(blocs));
	res = malloc(sizeof(char **) * (ft_astrlen(blocs) + 1));
	if (!res)
		return (free_all(blocs), NULL);
	while (blocs[i])
	{
		res[i] = ft_split_not_in_quotes(blocs[i], ' ');
		i++;
	}
	res[i] = NULL;
	put_aastring(res);

}
