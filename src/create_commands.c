/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:45:16 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/25 10:51:08 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	amount_fd(t_list **lst)
{
	t_list	**tmp;
	t_list	*tmp2;
	int		i;
	int		res;

	i = 0;
	res = 0;
	tmp = lst;
	while (tmp[i])
	{
		tmp2 = tmp[i];
		while (tmp2)
		{
			res += ((((char *)(tmp2->content))[0] == 7)
					|| (((char *)(tmp2->content))[0] == 10)
					|| (((char *)(tmp2->content))[0] == 8));
			tmp2 = tmp2->next;
		}
		i++;
	}
	return (res);
}

int	is_in_int(int lst, int a, int b, int c)
{
	return ((lst == a) || (lst == b) || (lst == c));
}

int	open_adequatly(char *file_name, int way)
{
	int	fd;

	if (way == -7)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (way == -8)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (way == -10)
		fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (fd);
}

int	*open_fds(t_list **lst)
{
	int		*fds;
	t_list	**tmp;
	t_list	*tmp2;
	int		i;
	int		j;

	fds = malloc(sizeof(int) * amount_fd(lst));
	if (!fds)
		return (NULL);
	tmp = lst;
	i = 0;
	j = 0;
	while (tmp[i])
	{
		tmp2 = tmp[i];
		while (tmp2)
		{
			if (is_in_int(((char *)(tmp2->content))[0], -7, -8, -10))
			{
				fds[j++] = open_adequatly(tmp2->next->content,
						((char *)(tmp2->content))[0]);
			}
			tmp2 = tmp2->next;

		}
		i++;
	}
	return (fds);
}


int	amount_fd_in_bloc(t_list *lst)
{
	t_list	*tmp;
	int		res;

	res = 0;
	tmp = lst;
	while (tmp)
	{
		if (is_in_int(((char *)tmp->content)[0], -7, -8, -10))
			res++;
		tmp = tmp->next;
	}
	return (res);
}

int	amount_hd_in_bloc(t_list *lst)
{
	t_list	*tmp;
	int		res;

	res = 0;
	tmp = lst;
	while (tmp)
	{
		if (((char *)tmp->content)[0] == 2)
			res++;
		tmp = tmp->next;
	}
	return (res);
}

t_command	*create_command(t_list *lst, char **hds, int *fds, t_env_var *vars)
{
	t_command	*res;
	char		*cmd;
	char		**args;
	t_list		*tmp;
	int			fd_in;
	int			ind_args;
	int			fd_out;
	char		*heredoc;

	cmd = NULL;
	heredoc = NULL;
	fd_in = 0;
	fd_out = 1;
	tmp = lst;
	ind_args = 0;
	args = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!args)
		return (NULL);
	while (tmp)
	{
		if ((((char *)(tmp->content))[0]) == 2)
		{
			heredoc = hds[0];
			hds++;
		}
		else if (is_in_int((((char *)(tmp->content))[0]), -7, -8, -10))
		{
			if ((((char *)(tmp->content))[0]) == -10)
				fd_in = fds[0];
			else
				fd_out = fds[0];
			fds++;
		}
		else
		{
			if (!cmd)
				cmd = ft_strdup(tmp->content);
			else
				args[ind_args++] = ft_strdup(tmp->content);
		}
		tmp = tmp->next;
	}
	args[ind_args] = NULL;
	res = init_command(cmd, args, vars);
	set_fd(&res, fd_in, fd_out, 2);
	set_heredoc(&res, heredoc);
	return (res);
}

t_command	**create_commands(t_list **lst, t_env_var *vars, char **hds)
{
	t_command	**cmds;
	int			*fds;
	int			fds_size;
	t_list		**tmp;
	int			hd_ind;
	int			fd_ind;
	int			i;

	i = 0;
	fd_ind = 0;
	hd_ind = 0;
	tmp = lst;
	fds_size = amount_fd(lst);
	(void) vars;
	cmds = NULL;
	if (lst)
		fds = open_fds(lst);
	while (tmp[i])
	{
		add_command(cmds, create_command(tmp[i], hds + hd_ind, fds + fd_ind, vars));
		hd_ind += amount_hd_in_bloc(tmp[i]);
		fd_ind += amount_fd_in_bloc(tmp[i]);
		i++;
	}
	return (cmds);
}
