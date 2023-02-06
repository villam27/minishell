/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:50:34 by tibernot          #+#    #+#             */
/*   Updated: 2023/02/06 11:54:15 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*to_gd_hd(char *str)
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
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (write(2, "did not malloc\n", 15), NULL);
	while (str[i])
	{
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		if (!is_in(str[i], "\'\"")
			|| (str[i] == '\'' && is_dquote)
			|| (str[i] == '\"' && is_quote))
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
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
			if (!in_quote(str, i) && !in_quote(str, i - 1))
			{
				i++;
				while (str[i] && is_in(str[i], " \f\n\t\v\r"))
					i++;
				j = while_out(str, i);
				ft_lstadd_back(&lst, ft_lstnew(to_gd_hd(ft_substr(str, i, j))));
				i += j - 1;
			}
		}
	}
	return (lst);
}

int	good_heredocs(char *str, t_list *hd)
{
	int		nb_hd;
	int		i;
	t_list	*tmp;

	tmp = hd;
	nb_hd = 0;
	i = 0;
	while (tmp)
	{
		if (!tmp->content)
			return (1);
		tmp = tmp->next;
		nb_hd++;
	}
	while (str[++i])
	{
		if (str[i] == '<' && str[i - 1] == '<'
			&& !in_quote(str, i) && !in_quote(str, i - 1))
			nb_hd--;
	}
	if (nb_hd != 0)
		return (0);
	return (1);
}

char	*do_heredoc(char *hd_out)
{
	t_do_heredoc_data	d;

	if (!set_do_heredoc_data(&d))
		return (NULL);
	d.pid = fork();
	if (d.pid < 0)
		return (close(d.pipes[0]), ft_putstr_fd("minishell: fork: Resource \
			 temporarily unavailable\n", 2), close(d.pipes[1]), NULL);
	signal(SIGINT, NULL);
	if (d.pid == 0)
	{
		if (!while_hd(hd_out, &d))
			return (exit(0), NULL);
		return (ft_putstr_fd(d.res, d.pipes[1]), exit(0), NULL);
	}
	waitpid(d.pid, (int *)signal(SIGINT, sigquit), 0);
	close(d.pipes[1]);
	return (d.res = get_lines(d.pipes[0]),
		close(d.pipes[0]), d.res);
}

char	**do_heredocs(char *str)
{
	t_list	*heredocs;
	t_list	*tmp;
	char	**res;
	int		i;

	i = 0;
	heredocs = create_heredocs(str);
	if (ft_lstsize(heredocs) == 0)
		return (NULL);
	if (!good_heredocs(str, heredocs))
		return (ft_lstclear(&heredocs, free), NULL);
	res = malloc(sizeof(char *) * (ft_lstsize(heredocs) + 1));
	if (!res)
		return (ft_lstclear(&heredocs, free), write(2, "did not malloc\n", 15),
			NULL);
	tmp = heredocs;
	while (tmp)
	{
		res[i] = do_heredoc(tmp->content);
		i++;
		tmp = tmp->next;
	}
	res[i] = NULL;
	ft_lstclear(&heredocs, free);
	return (res);
}
