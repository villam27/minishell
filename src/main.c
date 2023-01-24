/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/24 15:44:03 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "builtins.h"
#include <fcntl.h>
#include<stdio.h>

void	ft_print_env(t_env_var *var);

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_commands 	*cmds;
	t_env_var	*vars = NULL;
	char		**args;
	int			ret_code = 0;
//	int			fd_in;

	//fd_in = open("/dev/urandom", O_RDONLY);
	cmds = NULL;
	i = 0;
	ft_export(envp, &vars);
	i = 1;
	while (i < argc)
	{
		args = ft_split(argv[i], ' ');
		t_command *cmd;
		cmd = init_command(ft_strdup(args[0]), args, NULL);
		set_fd(&cmd, 0, 1, 2);
		//set_heredoc(&cmd, ft_strdup("Le prout"));
		add_command(&cmds, &cmd);
		i++;
	}
	run_everything(&cmds, &vars, &ret_code);
	ft_printf("---");
	ft_env(vars);
	while (vars)
	{
		ft_unset_single(vars->name, &vars);
	}
	ft_printf("ret_code: %d\n", ret_code);
	return (0);
}
