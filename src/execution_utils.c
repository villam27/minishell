/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:37:57 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/21 13:50:03 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
	return (0);
}

int	run_builtin(t_commands **cmds, t_env_var **vars)
{
	if (!ft_strcmp((*cmds)->cmd->cmd, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp((*cmds)->cmd->cmd, "cd"))
		return (ft_cd((*cmds)->cmd->args + 1, 0, *vars));
	if (!ft_strcmp((*cmds)->cmd->cmd, "echo"))
		return (ft_echo((*cmds)->cmd->args + 1, 1));
	if (!ft_strcmp((*cmds)->cmd->cmd, "export"))
		return (ft_export(NULL, NULL, vars));
	if (!ft_strcmp((*cmds)->cmd->cmd, "unset"))
		return (ft_unset((*cmds)->cmd->args[1], vars));
	if (!ft_strcmp((*cmds)->cmd->cmd, "env"))
		return (ft_env(*vars));
	return (0);
}
