/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:59:53 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/20 20:01:56 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"

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

static int	run_builtins(t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (exit(ft_pwd()), 1);
	return (0);
}

static void	multi_close(int p1[2], int p2[2])
{
	close(p1[0]);
	close(p1[1]);
	close(p2[0]);
	close(p2[1]);
}

static void	wait_cmds(int cmds_size)
{
	int	i;

	i = 0;
	while (i < cmds_size)
	{
		wait(NULL);
		i++;
	}
}

static pid_t	new_process(t_command *cmd, int pipe_old[2]
	, int pipe_new[2], t_commands *last)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		dup2(pipe_old[STDIN_FILENO], cmd->fd_in);
		if (last)
			dup2(pipe_new[STDOUT_FILENO], cmd->fd_out);
		else
			dup2(STDOUT_FILENO, cmd->fd_out);
		multi_close(pipe_old, pipe_new);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (!run_builtins(cmd))
			execve(cmd->cmd, cmd->args, NULL);
		ft_putstr_fd("a", 2);
	}
	return (pid);
}

int	run_cmds(t_commands **cmds_list)
{
	int	cmds_size;
	int	pipe_fd[2][2];

	cmds_size = size_commands(*cmds_list);
	if (pipe(pipe_fd[0]) < 0 || pipe(pipe_fd[1]) < 0)
		return (1);
	pipe_fd[0][0] = dup(0);
	pipe_fd[0][1] = dup(1);
	while ((*cmds_list))
	{
		new_process((*cmds_list)->cmd,
			pipe_fd[0], pipe_fd[1], (*cmds_list)->next);
		close(pipe_fd[0][0]);
		close(pipe_fd[0][1]);
		pipe_fd[0][0] = pipe_fd[1][0];
		pipe_fd[0][1] = pipe_fd[1][1];
		pipe(pipe_fd[1]);
		rm_command(cmds_list);
	}
	multi_close(pipe_fd[0], pipe_fd[1]);
	wait_cmds(cmds_size);
	return (0);
}
