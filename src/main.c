/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/12 19:20:27 by tibernot         ###   ########.fr       */
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
	/*add_history(line);
	if (parsing_errors(line))
		ft_putendl_fd("Parsing error", 2);*/
	while (line)
	{
		line = readline(user);
		add_history(line);
		if (parsing_errors(line))
			ft_putendl_fd("Parsing error", 2);
		else
			do_heredocs(line); // to change to do in a fork
		free(line);
	}
	/*get string without '<<'*/
	/*split on pipes*/
	/*do the command list*/
	/*exec commands*/
	/*free str*/
	return (0);
}
