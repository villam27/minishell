/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/14 13:07:13 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int			i;
	t_commands 	*cmds;
	char		**args;
	//int			fd_in[2];
	//int			fd_out[2];

	i = 1;
	cmds = NULL;
	/*fd_in[0] = open("Makefile", O_RDONLY);
	fd_out[0] = open("out", O_CREAT | O_WRONLY, 0644);
	fd_in[1] = open(".gitignore", O_RDONLY);
	fd_out[1] = open("out2", O_CREAT | O_WRONLY, 0644);*/
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
