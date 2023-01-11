/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/11 13:35:41 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	main(int argc, char **argv)
{
	int			i;
	t_commands 	*cmds;
	char		**args;

	i = 1;
	cmds = NULL;
	while (i < argc)
	{
		args = ft_split(argv[i], ' ');
		t_command *cmd;
		cmd = init_command(ft_strdup(args[0]), args, NULL);
		add_command(&cmds, &cmd);
		i++;		
	}
	run_cmds(&cmds);
	return (0);
}
