/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:37:03 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 10:39:45 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command(t_command **cmds_list, t_command *cmd)
{
	t_command	*temp;

	if (!cmds_list)
	{
		cmds_list = &cmd;
		return ;
	}
	temp = (*cmds_list);
	if (!temp)
	{
		(*cmds_list) = cmd;
		return ;
	}
	while (temp && temp->next)
		temp = temp->next;
	temp->next = cmd;
}

void	rm_command(t_command **cmds_list)
{
	t_command	*cmd;

	if (!(*cmds_list))
		return ;
	cmd = (*cmds_list);
	(*cmds_list) = (*cmds_list)->next;
	cmd->next = NULL;
	destroy_command(cmd);
	free(cmd);
}

int	size_commands(t_command *cmds_list)
{
	int			i;
	t_command	*temp;

	temp = cmds_list;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
