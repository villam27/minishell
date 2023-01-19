/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:50:34 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/19 11:14:41 by ratinax          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

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
	res = malloc(sizeof(char) * ft_strlen(str));
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
			if (!in_quote(str, i))
			{
				i++;
				while (str[i] && is_in(str[i], " \f\n\t\v\r"))
					i++;
				if (!str[i])
					return (NULL);
				j = while_out(str, i);
				ft_lstadd_back(&lst, ft_lstnew(to_gd_hd(ft_substr(str, i, j))));
				i += j;
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
		if (str[i] == '<' && str[i - 1] == '<')
		nb_hd--;
	}
	if (nb_hd != 0)
		return (0);
	return (1);
}

char	**do_heredoc(char *hd_out)
{
	int		pid;
	char	*line;
	t_list	*line_lst;

	line_lst = NULL;
	pid = fork();
	if (pid < 0)
		return (NULL);
	if (pid == 0)
	{
		line = readline("> ");
		if (ft_strncmp(hd_out, line, ft_strlen(hd_out)) != 0)
			line_lst = ft_lstnew((char *)line);
		while (ft_strncmp(hd_out, line, ft_strlen(hd_out)) != 0)
		{
			line = readline("> ");
			if (ft_strncmp(hd_out, line, ft_strlen(hd_out)) != 0)
				ft_lstadd_back(&line_lst, ft_lstnew((char *)line));
		}
		return (to_astr_endl(&line_lst));
	}
	waitpid(pid, NULL, 0);
	return (NULL);
}

char	**do_heredocs(char *str)
{
	t_list	*heredocs;
	t_list	*tmp;
	char	**res;

	res = NULL;
	heredocs = create_heredocs(str);
	if (!good_heredocs(str, heredocs))
		ft_lstclear(&heredocs, free);
	tmp = heredocs;
	while (tmp)
	{
		res = do_heredoc(tmp->content);
		if (tmp->next)
			free_all(res);
		tmp = tmp->next;
	}
	ft_lstclear(&heredocs, free);
	return (res);
}
