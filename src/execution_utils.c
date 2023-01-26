/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:37:57 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/26 10:06:13 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"

int	is_builtins(t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (1);
	return (0);
}

int	run_builtin(t_command **cmds, t_env_var **vars)
{
	int	temp;
	int	result;

	temp = dup(1);
	dup2((*cmds)->fd_out, STDOUT_FILENO);
	if (!ft_strcmp((*cmds)->cmd, "pwd"))
		result = ft_pwd();
	if (!ft_strcmp((*cmds)->cmd, "cd"))
		result = ft_cd((*cmds)->args + 1,
				arg_size((*cmds)->args + 1), *vars);
	if (!ft_strcmp((*cmds)->cmd, "echo"))
		result = ft_echo((*cmds)->args + 1,
				arg_size((*cmds)->args + 1));
	if (!ft_strcmp((*cmds)->cmd, "export"))
		result = ft_export((*cmds)->args, vars);
	if (!ft_strcmp((*cmds)->cmd, "unset"))
		result = ft_unset((*cmds)->args, vars);
	if (!ft_strcmp((*cmds)->cmd, "env"))
		result = ft_env(*vars);
	if (!ft_strcmp((*cmds)->cmd, "exit"))
		result = ft_exit((*cmds)->args + 1,
				arg_size((*cmds)->args) - 1, vars);
	dup2(temp, STDOUT_FILENO);
	rm_command(cmds);
	return (close(temp), result);
}

void	run_everything(t_command **cmds, t_env_var **vars, int *ret)
{
	int	r;

	if (!cmds)
		return ;
	if (size_commands(*cmds) == 1 && is_builtins(*cmds))
		r = run_builtin(cmds, vars);
	else if (size_commands(*cmds))
		r = run_cmds(cmds, vars);
	if (!*ret)
		*ret = r;
}

int	arg_size(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
