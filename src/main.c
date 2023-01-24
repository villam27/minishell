/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/24 17:24:18 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "builtins.h"

t_env_var	*init_cmds(char **envp)
{
	int			i;
	t_env_var	*vars;

	vars = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		ft_export(envp[i], &vars);
		i++;
	}
	return (vars);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**hds;
	t_list		**all_cmds;
	t_env_var	*vars;

	(void) argc;
	(void) argv;
	vars = NULL;
	vars = init_cmds(envp);
	line = "l";
	hds = NULL;
	all_cmds = NULL;
	while (line)
	{
		line = readline("Minishell$ ");
		if (!line)
		{
			while (vars)
				ft_unset(vars->name, &vars);
			return (clear_history(), free(line), 0);
		}
		if (line[0])
		{
			add_history(line);
			if (parsing_errors(line))
				ft_putendl_fd("Parsing error", 2);
			else
			{
				hds = do_heredocs(line); // do in a fork()
				/*
				if (hds)
					free_all(hds);
				*/ // give hds to create cmds
				all_cmds = get_all(line);
				to_good_cmds(all_cmds, &vars);
				// put_alst(all_cmds);
				// (void) all_cmds;
				// (void) vars;
				create_commands(all_cmds, vars);
				// open files etc..
				// create cmds
				// exec
				free_alist(all_cmds);
				free(line);
				free_all(hds);
			}
		}
	}
	/*do the command list*/
	/*exec commands*/
	return (0);
}

