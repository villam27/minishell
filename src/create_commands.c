/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:45:16 by tibernot          #+#    #+#             */
/*   Updated: 2023/02/06 12:41:59 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_open_fds_data	d;

	d.fds = malloc(sizeof(int) * (amount_fd(lst)));
	if (!d.fds)
		return (write(2, "did not malloc\n", 15), NULL);
	d.tmp = lst;
	d.i = -1;
	d.j = 0;
	while (d.tmp && d.tmp[++d.i])
	{
		d.tmp2 = d.tmp[d.i];
		while (d.tmp2)
		{
			if (d.tmp2->content
				&& is_in_int(((char *)(d.tmp2->content))[0], -7, -8, -10))
			{
				d.fds[d.j] = open_adequatly(d.tmp2->next->content,
						((char *)(d.tmp2->content))[0]);
				if (d.fds[d.j++] == -1)
					break ;
			}
			d.tmp2 = d.tmp2->next;
		}
	}
	return (d.fds);
}

int	good_fds(t_create_command_data *d, char **hds, int *fds)
{
	t_create_command_data	d_tmp;

	d_tmp = *d;
	while (d_tmp.tmp)
	{
		if ((d_tmp.tmp->content && (((char *)(d_tmp.tmp->content))[0]) == 2)
			&& (hds != NULL))
		{
			d->heredoc = hds[0];
			hds++;
		}
		else if (d_tmp.tmp->content
			&& is_in_int((((char *)(d_tmp.tmp->content))[0]), -7, -8, -10))
		{
			if (!change_fds(&(d->fd_in), &(d->fd_out),
					(((char *)(d_tmp.tmp->content))[0]), fds))
				return (0);
			fds++;
		}
		d_tmp.tmp = d_tmp.tmp->next;
	}
	if (d->fd_out == -15)
		d->fd_out = 1;
	d->fd_in = ((d->fd_in != -15) * d->fd_in);
	return (1);
}

t_command	*create_command(t_list *lst, char **hds, int *fds, t_env_var *vars)
{
	t_create_command_data	d;

	set_create_command_data(&d, lst);
	if (!d.args)
		return (NULL);
	if (!good_fds(&d, hds, fds))
		return (well_set_command(&d, vars, 1));
	while (d.tmp)
	{
		if (d.tmp->content && !d.pre_is_fd
			&& (((char *)(d.tmp->content))[0]) != 2
			&& !is_in_int((((char *)(d.tmp->content))[0]), -7, -8, -10))
		{
			if (!d.cmd)
				d.cmd = to_executable_cmd(d.tmp->content,
						ft_get_var_content(&vars, "PATH"));
			d.args[d.ind_args++] = ft_strdup(d.tmp->content);
		}
		d.pre_is_fd = (d.tmp->content
				&& is_in_int((((char *)(d.tmp->content))[0]), -7, -8, -10));
		d.tmp = d.tmp->next;
	}
	return (well_set_command(&d, vars, 0));
}

t_command	*create_commands(t_list **lst, t_env_var *vars, char **hds)
{
	t_create_commands_data	d;

	d.i = 0;
	d.fd_ind = 0;
	d.hd_ind = 0;
	d.tmp = lst;
	d.fds_size = amount_fd(lst);
	d.cmds = NULL;
	d.fds = open_fds(lst);
	while (d.tmp && d.tmp[d.i])
	{
		add_command(&(d.cmds),
			create_command(d.tmp[d.i], hds + d.hd_ind, d.fds + d.fd_ind, vars));
		d.hd_ind += amount_hd_in_bloc(d.tmp[d.i]);
		d.fd_ind += amount_fd_in_bloc(d.tmp[d.i]);
		d.i++;
	}
	free(d.fds);
	return (d.cmds);
}
