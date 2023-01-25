/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:05:31 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 10:40:12 by tibernot         ###   ########.fr       */
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
	command->fd_err = 2;
	command->fd_in = 0;
	command->fd_out = 1;
	command->ret_value = 0;
	command->here = NULL;
	command->next = NULL;
	return (command);
}

void	set_fd(t_command **cmd, int fd_in, int fd_out, int fd_err)
{
	(*cmd)->fd_err = fd_err;
	(*cmd)->fd_in = fd_in;
	(*cmd)->fd_out = fd_out;
}

void	set_heredoc(t_command **cmd, char *heredoc)
{
	(*cmd)->here = heredoc;
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
	if (cmd->here)
		free(cmd->here);
	free(cmd);
}
