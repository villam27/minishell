/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:50:34 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/10 15:56:02 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_list	*create_heredocs(char *str)
{
	int		i;
	int		j;
	t_list	*lst;

	lst = NULL;
	i = 1;
	while (str[i])
	{
		j = 0;
		if (str[i] == '<' && str[i - 1] == '<')
		{
			while (str[i] && is_in(str[i], ' \f\n\t\v\r'))
				i++;
			if (!str[i])
				return (NULL);
			if ((str[i] == '\"') || (str[i] == '\"'))
			{
				while (str[i + j] != str[i])
					j++;
			}
			else
			{
				while (!is_in(str[i + j], ' \f\n\t\v\r'))
					j++;
			}
		}
	}
}

void	do_heredocs(char *str)
{

}
