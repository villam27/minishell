/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:59:53 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/11 16:54:25 by alboudje         ###   ########.fr       */
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

/*pid_t	first_process(char *cmds, char **args, int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (dup2(pipe_fd[STDOUT_FILENO], STDOUT_FILENO) < 0
			|| close(pipe_fd[0]) < 0 || close(pipe_fd[1]) < 0)
		{
			exit(EXIT_FAILURE);
			return (-1);
		}
		if (execve(cmds, cmds, NULL) < 0)
			return (-1);
	}
	return (pid);
}
*/
pid_t	last_process(char *cmds, char **args, int pipe_old[2])
{
	pid_t	pid;
	//int		pipe_fd[2];
	ft_printf("here\n");

	//pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(pipe_old[STDIN_FILENO], STDIN_FILENO);
		close(pipe_old[0]);
		close(pipe_old[1]);
		execve(cmds, args, NULL);
	}
	//dup2(pipe_fd[STDOUT_FILENO], p[STDIN_FILENO]);
	//dup2(p[STDIN_FILENO], pipe_fd[STDIN_FILENO]);
	return (pid);
}

pid_t	new_process(char *cmds, char **args, int pipe_old[2], int pipe_new[2])
{
	pid_t	pid;
	//int		pipe_fd[2];
	ft_printf("here\n");

	//pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(pipe_new[STDOUT_FILENO], STDOUT_FILENO);
		dup2(pipe_old[STDIN_FILENO], STDIN_FILENO);
		close(pipe_old[0]);
		close(pipe_old[1]);
		close(pipe_new[0]);
		close(pipe_new[1]);
		execve(cmds, args, NULL);
	}
	//dup2(pipe_fd[STDOUT_FILENO], p[STDIN_FILENO]);
	//dup2(p[STDIN_FILENO], pipe_fd[STDIN_FILENO]);
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
	pipe_fd[0][0] = 0;
	while (i < cmds_size - 1)
	{
		ft_printf("%d\n", i);
		//print_cmd((*cmds_list)->cmd);
		new_process((*cmds_list)->cmd->cmd, (*cmds_list)->cmd->args, pipe_fd[0], pipe_fd[1]);
		close(pipe_fd[0][0]);
		close(pipe_fd[0][1]);
		pipe_fd[0][0] = pipe_fd[1][0];
		pipe_fd[0][1] = pipe_fd[1][1];
		pipe(pipe_fd[1]);
		rm_command(cmds_list);
		i++;
	}
	last_process((*cmds_list)->cmd->cmd, (*cmds_list)->cmd->args, pipe_fd[0]);
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
