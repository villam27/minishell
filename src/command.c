/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:05:31 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/10 13:46:44 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(char *cmd, char **args, t_env_var *vars)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd = cmd;
	command->args = args;
	command->vars = vars;
	command->fd_err = -1;
	command->fd_in = -1;
	command->fd_out = -1;
	return (command);
}

void	set_fd(t_command **cmd, int fd_in, int fd_out, int fd_err)
{
	(*cmd)->fd_err = fd_err;
	(*cmd)->fd_in = fd_in;
	(*cmd)->fd_out = fd_out;
}

void	destroy_command(t_command *cmd)
{
	free(cmd->cmd);
	free_all(cmd->args);
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	if (cmd->fd_err > 2)
		close(cmd->fd_err);
	free(cmd);
}
