/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:37:04 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/11 12:22:51 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"

typedef struct s_env_var
{
	char				*name;
	char				*content;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_command
{
	int			fd_in;
	int			fd_out;
	int			fd_err;
	char		*cmd;
	char		**args;
	t_env_var	*vars;
}	t_command;

typedef struct s_commands
{
	t_command			*cmd;
	struct s_commands	*next;
}	t_commands;

/*
	command init and destruction
*/
t_command	*init_command(char *cmd, char **args, t_env_var *vars);
void		set_fd(t_command **cmd, int fd_in, int fd_out, int fd_err);
void		destroy_command(t_command *cmd);

t_commands	*init_commands(void);
void		add_command(t_commands **cmds_list, t_command **cmd);
void		rm_command(t_commands **cmds_list);
int			size_commands(t_commands *cmds_list);

/*
	env variables functions
*/
t_env_var	*new_var(char *name, char *content);
void		free_var(t_env_var *var);
void		add_var(t_env_var *vars, t_env_var *new_var);
void		destroy_vars(t_env_var **vars);

#endif