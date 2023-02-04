/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:59:53 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/28 14:11:54 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"
#include "minishell.h"
#include <fcntl.h>

static int	child_process(t_command *cmd, int pipes[2][2],
	t_command *last, t_env_var **vars)
{
	char	**envp;

	if (cmd->here)
		cmd->fd_in = get_heredoc_fd(cmd->here);
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
	{
		g_err = 0;
		envp = get_envp(*vars);
		if (execve(cmd->cmd, cmd->args, envp) < 0)
			return (good_error_message(cmd->cmd),
				free_all(envp), exit(127), -1);
	}
	return (g_err = 0, exit(0), 0);
}

static int	new_process(t_command *cmd, int pipes[2][2],
	t_command *last, t_env_var **vars)
{
	pid_t	pid;

	signal(SIGINT, &intquit);
	signal(SIGQUIT, &sigquit_process);
	g_err = 0;
	pid = fork();
	if (pid < 0)
		return ((void)ft_putstr_fd("minishell: fork: Resource \
temporarily unavailable\n", 2), -1);
	if (pid == 0)
	{
		if (child_process(cmd, pipes, last, vars) < 0)
			return (-1);
	}
	return (pid);
}

int	wait_cmds(int cmds_size, int *pids)
{
	int	i;
	int	ret;

	i = 0;
	while (i < cmds_size)
	{
		ret = get_process_return(pids[i]);
		i++;
	}
	free(pids);
	return (ret);
}

void	modify_pipe(int pipe_fd[2][2])
{
	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);
	pipe_fd[0][0] = pipe_fd[1][0];
	pipe_fd[0][1] = pipe_fd[1][1];
	if (pipe(pipe_fd[1]) < 0)
		return ;
}

int	run_cmds(t_command **cmds_list, t_env_var **vars)
{
	int	cmds_size;
	int	pipe_fd[2][2];
	int	*pids;
	int	i;

	(void) vars;
	i = -1;
	cmds_size = size_commands(*cmds_list);
	pids = malloc(sizeof(int) * cmds_size);
	if (!pids || pipe(pipe_fd[1]) < 0)
		return (free(pids), 1);
	pipe_fd[0][0] = dup(0);
	pipe_fd[0][1] = dup(1);
	while (++i < cmds_size)
	{
		pids[i] = new_process(*cmds_list,
				pipe_fd, (*cmds_list)->next, vars);
		if (pids[i] < 0)
			return (exit_all_fork_broken(pipe_fd, i, pids, cmds_list));
		modify_pipe(pipe_fd);
		rm_command(cmds_list);
	}
	while (*cmds_list)
		rm_command(cmds_list);
	return (multi_close(pipe_fd[0], pipe_fd[1]), wait_cmds(cmds_size, pids));
}
