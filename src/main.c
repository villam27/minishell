/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/21 19:32:04 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "builtins.h"
#include <fcntl.h>

void	ft_print_env(t_env_var *var);

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_commands 	*cmds;
	t_env_var	*vars = NULL;
	char		**args;

	cmds = NULL;
	i = 0;
	while (envp[i])
	{
		char **sp = ft_split(envp[i], '=');
		ft_export(sp[0], sp[1], &vars);
		free_all(sp);
		i++;
	}
	i = 1;
	while (i < argc)
	{
		args = ft_split(argv[i], ' ');
		t_command *cmd;
		cmd = init_command(ft_strdup(args[0]), args, NULL);
		add_command(&cmds, &cmd);
		i++;	
	}
	ft_env(vars);
	run_everything(&cmds, &vars);	
	ft_printf("---");
	ft_env(vars);
	while (vars)
	{
		ft_unset(vars->name, &vars);
	}
	return (0);
}
