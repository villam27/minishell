/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:45:16 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/25 12:08:48 by tibernot         ###   ########.fr       */
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
			res += ((((char *)(tmp2->content))[0] == -7)
					|| (((char *)(tmp2->content))[0] == -10)
					|| (((char *)(tmp2->content))[0] == -8));
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

	fds = malloc(sizeof(int) * (amount_fd(lst) + 1));
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

void	set_create_command_data(t_create_command *d, t_list *lst)
{
	d->pre_is_fd_o_hd = 0;
	d->cmd = NULL;
	d->heredoc = NULL;
	d->fd_in = 0;
	d->fd_out = 1;
	d->tmp = lst;
	d->ind_args = 0;
	d->args = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	return (0);
}

t_command	*create_command(t_list *lst, char **hds, int *fds, t_env_var *vars)
{
	t_create_command	d;

	set_create_command_data(&d, lst);
	if (!d.args)
		return (NULL);
	while (d.tmp)
	{
		if ((((char *)(d.tmp->content))[0]) == 2)
		{
			d.pre_is_fd_o_hd = 1;
			d.heredoc = hds[0];
			hds++;
		}
		else if (is_in_int((((char *)(d.tmp->content))[0]), -7, -8, -10))
		{
			if ((((char *)(d.tmp->content))[0]) == -10)
				d.fd_in = fds[0];
			else
				d.fd_out = fds[0];
			if (d.fd_in == -1 || d.fd_out == -1)
				return (init_command(NULL, NULL, vars));
			d.pre_is_fd_o_hd = 1;
			fds++;
		}
		else if (!d.pre_is_fd_o_hd)
		{
			if (!d.cmd)
			{
				if (is_builtin(d.tmp->content))
					d.cmd = ft_strdup(d.tmp->content);
				else
				{
					if (!good_cmd(d.tmp->content, ft_get_var_content(&vars, "PATH")))
						return (init_command(NULL, NULL, vars));
					d.cmd = to_executable_cmd(d.tmp->content, ft_get_var_content(&vars, "PATH"));
				}
			}
			d.args[d.ind_args++] = ft_strdup(d.tmp->content);
			d.pre_is_fd_o_hd = 0;
		}
		d.tmp = d.tmp->next;
	}
	d.args[d.ind_args] = NULL;
	d.res = init_command(d.cmd, d.args, vars);
	return (set_fd(&(d.res), d.fd_in, d.fd_out, 2),
		set_heredoc(&(d.res), d.heredoc), d.res);
}

t_command	*create_commands(t_list **lst, t_env_var *vars, char **hds)
{
	t_command	*cmds;
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
		add_command(&cmds, create_command(tmp[i], hds + hd_ind, fds + fd_ind, vars));

		hd_ind += amount_hd_in_bloc(tmp[i]);
		fd_ind += amount_fd_in_bloc(tmp[i]);
		i++;
	}
	return (cmds);
}
