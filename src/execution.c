/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:59:53 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/21 16:00:35 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"

static int	run_builtins(t_command *cmd, t_env_var **vars)
{
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (exit(ft_pwd()), 1);
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (exit(ft_cd(cmd->args + 1,
					arg_size(cmd->args + 1), *vars)), 1);
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (exit(ft_echo(cmd->args + 1,
					arg_size(cmd->args + 1))), 1);
	if (!ft_strcmp(cmd->cmd, "export"))
		return (exit(ft_export(NULL, NULL, vars)), 1);
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (exit(ft_unset(cmd->args[1], vars)), 1);
	if (!ft_strcmp(cmd->cmd, "env"))
		return (exit(ft_env(*vars)), 1);
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

static pid_t	new_process(t_command *cmd, int pipes[2][2],
	t_commands *last, t_env_var **vars)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		dup2(pipes[0][STDIN_FILENO], cmd->fd_in);
		if (last)
			dup2(pipes[1][STDOUT_FILENO], cmd->fd_out);
		else
			dup2(STDOUT_FILENO, cmd->fd_out);
		multi_close(pipes[0], pipes[1]);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (!run_builtins(cmd, vars))
			execve(cmd->cmd, cmd->args, NULL);
	}
	return (pid);
}

int	run_cmds(t_commands **cmds_list, t_env_var **vars)
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
			pipe_fd, (*cmds_list)->next, vars);
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
