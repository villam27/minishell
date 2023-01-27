/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:38:52 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/27 17:47:59 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtins.h"
#include "minishell.h"

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

void	parse_exec(t_main_data *d)
{
	g_err = (g_err * (d->line[0] != '\0'));
	d->hds = do_heredocs(d->line);
	d->all_cmds = get_all(d->line);
	to_good_cmds(d->all_cmds, &(d->vars));
	tcsetattr(STDIN_FILENO, TCSANOW, &(d->save));
	d->cmds = create_commands(d->all_cmds, d->vars, d->hds);
	if (d->cmds)
		run_everything(&(d->cmds), &(d->vars));
	else
		rm_command(&(d->cmds));
	free_alist(d->all_cmds);
	free_all(d->hds);
}

void	set_main_data(t_main_data *d, int argc, char **argv, char **envp)
{
	tcgetattr(STDIN_FILENO, &(d->save));
	tcgetattr(STDIN_FILENO, &(d->term));
	d->term.c_lflag &= ECHO;
	d->cmds = NULL;
	(void) argc;
	(void) argv;
	d->vars = init_cmds(envp);
	d->line = "l";
	d->hds = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_main_data	d;

	set_main_data(&d, argc, argv, envp);
	while (d.line)
	{
		handle_input(&(d.term));
		d.line = readline("Minishell$ ");
		if (!d.line)
		{
			while (d.vars)
				ft_unset_single(d.vars->name, &(d.vars));
			tcsetattr(STDIN_FILENO, TCSANOW, &(d.save));
			return (clear_history(), free(d.line), printf("exit\n"), exit(0), 0);
		}
		else
		{
			add_history(d.line);
			if (parsing_errors(d.line))
				ft_putendl_fd("Parsing error", 2);
			else
				parse_exec(&d);
			free(d.line);
		}
	}
	return (0);
}
