/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/21 15:16:15 by alboudje         ###   ########.fr       */
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
	//int			fd_in[2];
	//int			fd_out[2];

	cmds = NULL;
	(void)envp;
	/*fd_in[0] = open("Makefile", O_RDONLY);
	fd_out[0] = open("out", O_CREAT | O_WRONLY, 0644);
	fd_in[1] = open(".gitignore", O_RDONLY);
	fd_out[1] = open("out2", O_CREAT | O_WRONLY, 0644);*/
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
		//set_fd(&cmd, fd_in[i - 1], fd_out[i - 1], 2);
		add_command(&cmds, &cmd);
		i++;	
	}
	run_everything(&cmds, &vars);	
	ft_pwd();
	while (vars)
	{
		ft_unset(vars->name, &vars);
	}
	return (0);
}
