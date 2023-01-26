/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:50:34 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/26 10:22:10 by tibernot         ###   ########.fr       */
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
	while (str[i])
	{
		is_quote = is_quote ^ ((str[i] == '\'') * !is_dquote);
		is_dquote = is_dquote ^ ((str[i] == '\"') * !is_quote);
		if (!is_in(str[i], "\'\"")
			|| (str[i] == '\'' && is_dquote)
			|| (str[i] == '\"' && is_quote))
		{
			res[j++] = str[i];
		}
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
	char	*line;
	char	*res;
	pid_t	pid;
	int		pipes[2];

	res = NULL;
	pipe(pipes);
	pid = fork();
	if (pid < 0)
		return ((void)ft_putstr_fd("minishell: fork: Resource \
			 temporarily unavailable\n", 2), NULL);
	if (pid == 0)
	{
		line = readline("> ");
		if (ft_strcmp(hd_out, line) != 0)
			res = str_append(res, line, "\n");
		if (!line)
			return (res);
		while (ft_strcmp(hd_out, line) != 0)
		{
			free(line);
			line = readline("> ");
			if (!line)
				exit(0);
			if (ft_strcmp(hd_out, line) != 0)
				res = str_append(res, line, "\n");
		}
		ft_putstr_fd(res, pipes[1]);
		exit(0);
	}
	wait(NULL);
	res = get_next_line(pipes[0]);
	ft_printf("%s\n", res);
	close(pipes[0]);
	close(pipes[1]);
	return (res);
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
		ft_lstclear(&heredocs, free);
	res = malloc(sizeof(char *) * (ft_lstsize(heredocs) + 1));
	if (!res)
		return (NULL);
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
