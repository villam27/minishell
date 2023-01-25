/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:00:12 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 11:25:54 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

void	run_everything(t_commands **cmds_list, t_env_var **vars, int *ret);

int		run_cmds(t_commands **cmds_list, t_env_var **vars);
void	print_cmd(t_command *cmd);
int		arg_size(char **args);

int		is_builtins(t_command *cmd);
int		run_builtin(t_commands **cmds, t_env_var **vars);

int		run_builtins(t_command *cmd, t_env_var **vars);
void	multi_close(int p1[2], int p2[2]);
int		get_process_return(int pid);
int		get_heredoc_fd(char *here);

#endif