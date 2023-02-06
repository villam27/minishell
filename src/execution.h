/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:00:12 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 13:14:20 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>

void	run_everything(t_command **cmds_list, t_env_var **vars);

int		run_cmds(t_command **cmds_list, t_env_var **vars, int *pids);
void	print_cmd(t_command *cmd);
int		arg_size(char **args);

int		is_builtins(t_command *cmd);
int		run_builtin(t_command **cmds, t_env_var **vars);

int		run_builtins(t_command *cmd, t_env_var **vars);
void	multi_close(int p1[2], int p2[2]);
int		get_process_return(int pid);
int		get_heredoc_fd(char *here);

int		exit_all_fork_broken(int pipe_fd[2][2],
			int size, int *pids, t_command **cmds_list);

int		wait_cmds(int cmds_size, int *pids);
void	good_error_message(char *str, char **envp);
#endif
