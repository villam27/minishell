/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:50:34 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/12 18:51:13 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	while_out(char *str, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (str[i + j] && str[i + j] != ' ')
	{
		if (is_in(str[i + j], "\'\""))
		{
			k = 1;
			while (str[i + j + k] && str[i + j + k] !=  str[i + j])
				k++;
			j += k;
		}
		else
			j++;
	}
	return (j);
}

int	in_quote(char *str, int index)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			while (str[i] && str[i] == '\"')
				i++;
		}
		if (str[i] == '\'')
		{
			while (str[i] && str[i] == '\'')
				i++;
		}
		if (i == index)
			return (0);
		if (i > index)
			return (1);
		i++;
	}
	return (0);
}

char	*to_good_heredoc(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		is_quote;
	int		is_dquote;

	i = 0;
	j = 0;
	is_quote = 0;
	is_dquote = 0;
	res = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		if (!is_in(str[i], "\'\"")
			|| (str[i] == '\'' && is_dquote)
			|| (str[i] == '\"' && is_quote))
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	return (free(str), res);
}

t_list	*create_heredocs(char *str)
{
	int		i;
	int		j;
	t_list	*lst;

	lst = NULL;
	i = 0;
	while (str && str[0] && str[1] && str[++i])
	{
		j = 0;
		if (str[i] == '<' && str[i - 1] == '<')
		{
			i++;
			while (str[i] && is_in(str[i], " \f\n\t\v\r"))
				i++;
			if (!str[i])
				return (NULL);
			j = while_out(str, i);
			/*if (!is_in(str[i], "\'\""))
				i++;*/
			ft_lstadd_back(&lst, ft_lstnew(to_good_heredoc(ft_substr(str, i, j))));
			ft_printf("%s", to_good_heredoc(ft_substr(str, i, j)));
			i += j;
		}
	}
	return (lst);
}

int	good_heredocs(char	*str, t_list *hd)
{
	int		nb_hd;
	int		i;
	t_list	*tmp;

	tmp = hd;
	nb_hd = 0;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		nb_hd++;
	}
	while (str[++i])
	{
		if (str[
			i] == '<' && str[i - 1] == '<')
		nb_hd--;
	}
	if (nb_hd != 0)
		return (0);
	return (1);
}

void	do_heredoc(char *hd_out)
{
	char	*line;

	line = readline("> ");
	while (ft_strncmp(hd_out, line, ft_strlen(hd_out)) != 0)
	{
		free(line);
		line = readline("> ");
	}
	free(line);
}

void	do_heredocs(char *str)
{
	t_list	*heredocs;
	t_list	*tmp;

	heredocs = create_heredocs(str);
	if (!good_heredocs(str, heredocs))
		ft_lstclear(&heredocs, free);
	tmp = heredocs;
	while (tmp)
	{
		do_heredoc(tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&heredocs, free);
}
/*jusqu a espcae oou "*/
