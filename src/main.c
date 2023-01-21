/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratinax <ratinax@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/21 09:52:49 by ratinax          ###   ########.fr       */
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

	(void) argc;
	(void) argv;
	(void) envp;
	user = "tibernot$ ";
	/*init env_vars*/
	/*while do prompt*/
	/*get signal quit*/
	/*add_historique*/
	/*get string in str*/
	line = "l";
	hds = NULL;
	while (line)
	{
		line = readline(user);
		add_history(line);
		if (parsing_errors(line))
			ft_putendl_fd("Parsing error", 2);
		else
			hds = do_heredocs(line); // to change to do in a fork

		if (hds)
			put_astring(hds);
		if (hds)
			free_all(hds);
		free(line);
	}
	/*get string without '<<'*/
	/*split on pipes*/
	/*do the command list*/
	/*exec commands*/
	/*free str*/
	return (0);
}
