/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:37:03 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/23 14:03:03 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*new_command(t_command **cmd)
{
	t_commands	*cmds_list;

	cmds_list = malloc(sizeof(t_commands));
	if (!cmds_list)
		return (NULL);
	cmds_list->cmd = *cmd;
	cmds_list->next = NULL;
	return (cmds_list);
}

void	add_command(t_commands **cmds_list, t_command **cmd)
{
	t_commands	*temp;

	temp = (*cmds_list);
	if (!temp)
	{
		(*cmds_list) = new_command(cmd);
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_command(cmd);
}

void	rm_command(t_commands **cmds_list)
{
	t_commands	*cmd;

	if (!(*cmds_list))
		return ;
	cmd = (*cmds_list);
	(*cmds_list) = (*cmds_list)->next;
	cmd->next = NULL;
	destroy_command(cmd->cmd);
	free(cmd);
}

int	size_commands(t_commands *cmds_list)
{
	int			i;
	t_commands	*temp;

	temp = cmds_list;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
