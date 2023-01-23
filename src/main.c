/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/23 15:59:40 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	prompt() //put hte prompt and exec in that function
{

}
*/

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*user;
	char	**hds;
	char	***cmds;
	t_list	**all_cmds;

	(void) argc;
	(void) argv;
	(void) envp;
	user = "Minishell$ ";
	/*init env_vars*/
	/*while do prompt*/
	/*get signal quit*/
	line = "l";
	hds = NULL;
	cmds = NULL;
	while (line)
	{
		line = readline(user);
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

