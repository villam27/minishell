/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:05:31 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 13:26:55 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_command(char *cmd, char **args, t_env_var *vars)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (write(2, "did not malloc\n", 15), NULL);
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

void	close_fds(int in, int out)
{
	if (in > 2)
		close(in);
	if (out > 2)
		close(out);
}

void	destroy_command(t_command *cmd)
{
	free(cmd->cmd);
	free_all(cmd->args);
	close_fds(cmd->fd_in, cmd->fd_out);
	if (cmd->fd_err > 2)
		close(cmd->fd_err);
	free(cmd);
}
