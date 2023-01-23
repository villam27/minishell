/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:37:04 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/23 12:37:04 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

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
	char		*heredoc;
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

void		add_command(t_commands **cmds_list, t_command *cmd);
void		rm_command(t_commands **cmds_list);

/*
	env variables functions
*/
t_env_var	*new_var(char *name, char *content);
void		free_var(t_env_var *var);
void		add_var(t_env_var *vars, t_env_var *new_var);
void		destroy_vars(t_env_var **vars);
/*
	Parsing
*/
int			parsing_errors(char *str);
/*
	Heredocs
*/
t_list		*create_heredocs(char *str);
char		**do_heredocs(char *str);
/*
	Utils
*/
int			is_in(char c, char *str);
void		put_astring(char **str);
char		**ft_split_not_in_quotes(char *s, char c);
char		***get_all(char	*line, int	*fds);
/*heredoc utils*/
int			in_quote(char *str, int index);
int			while_out(char *str, int i);
char		*str_append(char *origin, char *str2, char *str3);
/*Parse and split utils*/
void		free_aastring(char ***str);
void		put_aastring(char ***str);
size_t		ft_astrlen(char **str);
size_t		ft_aastrlen(char ***astr);
void		free_alist(t_list **alst);
char		*str_to_chr(char *str, char c);
void		rm_heredoc(t_list *lst);
void		rm_heredocs(t_list **lst);
void		update_string_hd(t_list *lst, int i);
t_list		**aastr_to_at_list(char ***aastr);
t_list		*get_beggining(char	*str, int i);
t_list		*get_end(char *str, int i);
t_list		*get_end_hd(char *str, int i);
t_list		*astr_to_t_list(char **str);
void		replace_file_in_file_outs(t_list **lst);
void		invert(t_list *lst, t_list *lst2);
/*lst utils*/
void		put_lst(t_list	*lst);
void		put_alst(t_list **alst);
#endif
