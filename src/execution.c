/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:59:53 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/14 14:58:08 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_cmd(t_command *cmd)
{
	int	i;

	i = 0;
	ft_printf("command: %s\n", cmd->cmd);
	while (cmd->args[i])
	{
		ft_printf("arg %d: %s\n", i, cmd->args[i]);
		i++;
	}
	ft_printf("in: %d, out %d, err %d\n", cmd->fd_in, cmd->fd_out, cmd->fd_err);
}

pid_t	last_process(t_command *cmd, int pipe_old[2])
{
	pid_t	pid;
	ft_printf("here last\n");

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		dup2(pipe_old[STDIN_FILENO], cmd->fd_in);
		dup2(STDOUT_FILENO, cmd->fd_out);
		close(pipe_old[0]);
		close(pipe_old[1]);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		execve(cmd->cmd, cmd->args, NULL);
	}
	return (pid);
}

pid_t	new_process(t_command *cmd, int pipe_old[2], int pipe_new[2])
{
	pid_t	pid;
	ft_printf("here\n");

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		dup2(pipe_new[STDOUT_FILENO], cmd->fd_out);
		dup2(pipe_old[STDIN_FILENO], cmd->fd_in);
		close(pipe_old[0]);
		close(pipe_old[1]);
		close(pipe_new[0]);
		close(pipe_new[1]);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		execve(cmd->cmd, cmd->args, NULL);
	}
	return (pid);
}

int	run_cmds(t_commands **cmds_list)
{
	int	cmds_size;
	int	i;
	int	pipe_fd[2][2];

	i = 0;
	cmds_size = size_commands(*cmds_list);
	pipe(pipe_fd[0]);
	pipe(pipe_fd[1]);
	pipe_fd[0][0] = dup(0);
	pipe_fd[0][1] = dup(1);
	while (i < cmds_size - 1)
	{
		new_process((*cmds_list)->cmd, pipe_fd[0], pipe_fd[1]);
		close(pipe_fd[0][0]);
		close(pipe_fd[0][1]);
		pipe_fd[0][0] = pipe_fd[1][0];
		pipe_fd[0][1] = pipe_fd[1][1];
		pipe(pipe_fd[1]);
		rm_command(cmds_list);
		i++;
	}
	last_process((*cmds_list)->cmd , pipe_fd[0]);
	rm_command(cmds_list);
	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);
	close(pipe_fd[1][0]);
	close(pipe_fd[1][1]);
	i = 0;
	while (i < cmds_size)
	{
		wait(NULL);
		i++;
	}
	return (0);
}
