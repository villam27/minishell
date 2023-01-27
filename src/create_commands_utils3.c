/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:52:24 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 18:07:59 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*well_set_command(t_create_command_data	*d,
	t_env_var *vars, int is_wrong)
{
	if (d->heredoc && !d->cmd)
		return (NULL);
	if (!d->cmd)
		d->cmd = ft_strdup("\0");
	d->args[d->ind_args] = NULL;
	if (is_wrong)
		d->r = init_command(NULL, NULL, vars);
	else
		d->r = init_command(d->cmd, d->args, vars);
	set_fd(&(d->r), d->fd_in, d->fd_out, 2);
	set_heredoc(&(d->r), d->heredoc);
	return (d->r);
}

void	split_alst_on_space(t_list **cmds)
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*pre_tmp;

	i = 0;
	pre_tmp = NULL;
	while (cmds[i])
	{
		tmp = cmds[i];
		while (tmp)
		{
			if (count_words_not_in_quote(tmp->content, ' ') > 1)
			{
				tmp2 = split_lst_on_space(&tmp, &pre_tmp);
				ft_lstdelone(tmp, free);
				if (!pre_tmp)
					cmds[i] = tmp2;
				tmp = tmp2;
			}
			pre_tmp = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}
