/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/10 13:51:12 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	print_cmd(t_command *cmd)
{
	int	i;

	i = 0;
	ft_printf("command: %s\n", cmd->cmd);
	while (cmd->args[i])
	{
		ft_printf("arg %d: %s\n", i, cmd->args[i]);
		i++;
	}
	ft_printf("in: %d, out %d, err %d\n", cmd->fd_in, cmd->fd_out, cmd->fd_err);
}*/

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	return (0);
}
