/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/23 17:34:41 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "builtins.h"

t_env_var	*init_cmds(char **envp)
{
	int			i;
	t_env_var	*vars;

	i = 0;
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

	vars = init_cmds(envp);
	
	line = "l";
	hds = NULL;
	while (line)
	{
		line = readline("Minishell$ ");
		if (line[0] == 'e')
			return (clear_history(), free(line), 0);
		if (line[0])
		{
			add_history(line);
			if (parsing_errors(line))
				ft_putendl_fd("Parsing error", 2);
			else
			{
				hds = do_heredocs(line); // to change to do in a fork
				if (hds)
					put_astring(hds);
				if (hds)
					free_all(hds);
				all_cmds = get_all(line);
				// to_good_cmds(all_cmds);
				free_alist(all_cmds);
				free(line);
			}
		}
	}
	/*split on pipes*/
	/*do the command list*/
	/*exec commands*/
	/*free str*/
	return (0);
}

