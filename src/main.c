/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:38:52 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 11:55:03 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"

int	g_err = 0;

t_env_var	*init_cmds(char **envp)
{
	int			i;
	t_env_var	*vars;

	vars = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	ft_export(envp, &vars);
	check_shlvl(&vars);
	return (vars);
}

void	handle_input(struct termios *term)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, term);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**hds;
	t_list		**all_cmds;
	t_env_var	*vars;
	t_command	*cmds;
	struct termios	save;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &save);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ECHO;
	cmds = NULL;
	(void) argc;
	(void) argv;
	vars = init_cmds(envp);
	line = "l";
	hds = NULL;
	while (line)
	{
		g_err = 0;
		handle_input(&term);
		line = readline("Minishell$ ");
		if (!line)
		{
			while (vars)
				ft_unset_single(vars->name, &vars);
			tcsetattr(STDIN_FILENO, TCSANOW, &save);
			return (clear_history(), free(line), ft_printf("exit\n"), exit(0), 0);
		}
		else
		{
			add_history(line);
			if (parsing_errors(line))
				ft_putendl_fd("Parsing error", 2);
			else
			{
				hds = do_heredocs(line);
				all_cmds = get_all(line);
				to_good_cmds(all_cmds, &vars);
				tcsetattr(STDIN_FILENO, TCSANOW, &save);
				cmds = create_commands(all_cmds, vars, hds);
				run_everything(&cmds, &vars);
				free_alist(all_cmds);
				free(line);
				free_all(hds);
			}
		}
	}
	return (0);
}
