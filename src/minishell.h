/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:37:04 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/07 13:08:07 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int	g_err;

typedef struct s_env_var
{
	char				*name;
	char				*content;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_command
{
	int					fd_in;
	int					fd_out;
	int					fd_err;
	int					ret_value;
	char				*here;
	char				*cmd;
	char				**args;
	t_env_var			*vars;
	struct s_command	*next;
}	t_command;

/*data structures*/

typedef struct s_create_command_data
{
	t_command	*r;
	char		*cmd;
	char		**args;
	t_list		*tmp;
	int			fd_in;
	int			ind_args;
	int			fd_out;
	char		*heredoc;
	int			pre_is_fd;

}	t_create_command_data;

typedef struct s_open_fds_data
{
	int		*fds;
	t_list	**tmp;
	t_list	*tmp2;
	int		i;
	int		j;

}	t_open_fds_data;

typedef struct s_create_commands_data
{
	t_command	*cmds;
	int			*fds;
	int			fds_size;
	t_list		**tmp;
	int			hd_ind;
	int			fd_ind;
	int			i;

}	t_create_commands_data;

typedef struct s_do_heredoc_data
{
	char	*line;
	char	*res;
	pid_t	pid;
	int		pipes[2];
	int		nb_lines;
	char	*str_nb_lines;

}	t_do_heredoc_data;

typedef struct s_fd_and_hd
{
	int		*fds;
	char	**hds;

}	t_fd_and_hd;

typedef struct s_var_to_content_data
{
	int			j;
	char		*end;
	char		*var_name;
	char		*res;
	char		*start;
	t_env_var	**vars;
}	t_var_to_content_data;

typedef struct s_main_data
{
	char			*line;
	char			**hds;
	t_list			**all_cmds;
	t_env_var		*vars;
	t_command		*cmds;
	struct termios	save;
	struct termios	term;
}	t_main_data;

typedef struct s_s_wthout_e_quote2_data
{
	char	*res;
	int		i;
	int		is_quote;
	int		is_dquote;
	int		j;
}	t_s_wthout_e_quote2_data;

typedef struct s_to_good_args_data
{
	t_list	**tmp;
	t_list	*tmp2;
	t_list	**change_vars;
	int		i;
	char	*pre_str;
	int		j;
}	t_to_good_args_data;

typedef struct s_split_alst_on_space_data
{
	int		i;
	t_list	*tmp;
	t_list	*tmp2;
	t_list	*pre_tmp;
}	t_split_alst_on_space_data;

/*
	command init and destruction
*/
t_command	*init_command(char *cmd, char **args, t_env_var *vars);
void		set_fd(t_command **cmd, int fd_in, int fd_out, int fd_err);
void		set_heredoc(t_command **cmd, char *heredoc);
void		close_fds(int in, int out);
void		destroy_command(t_command *cmd);

void		add_command(t_command **cmds_list, t_command *cmd);
void		rm_command(t_command **cmds_list);
int			size_commands(t_command *cmds_list);
/*
	env variables functions
*/
t_env_var	*new_var(char *name, char *content);
void		free_var(t_env_var *var);
void		add_var(t_env_var *vars, t_env_var *new_var);
void		destroy_vars(t_env_var **vars);
char		*ft_get_var_content(t_env_var **vars, char *name);
/*
	Parsing
*/
int			parsing_errors(char *str);
void		to_good_cmds(t_list **cmds, t_env_var **vars);
/*Create commands*/
t_command	*create_commands(t_list **lst, t_env_var *vars, char **hds);
char		*to_executable_cmd(char *str, char *path);
/*Create commands utils*/
int			amount_fd(t_list **lst);
void		set_create_command_data(t_create_command_data *d, t_list *lst);
int			amount_hd_in_bloc(t_list *lst);
int			amount_fd_in_bloc(t_list *lst);
int			is_in_int(int lst, int a, int b, int c);
int			is_builtin_str(char *str);
int			change_fds(int *fd_in, int *fd_out, int way, int *fds);
t_list		*split_lst_on_space(t_list **lst, t_list **pre_lst);
t_command	*well_set_command(t_create_command_data	*d,
				t_env_var *vars, int is_wrong);
/*
	Heredocs
*/
t_list		*create_heredocs(char *str);
char		**do_heredocs(char *str);
/*heredoc utils*/
int			while_out(char *str, int i);
char		*str_append(char *origin, char *str2, char *str3);
int			set_do_heredoc_data(t_do_heredoc_data *d);
int			while_hd(char *hd_out, t_do_heredoc_data *d);
/*
	Utils
*/
int			is_in(char c, char *str);
void		put_astring(char **str);
char		**ft_split_not_in_quotes(char *s, char c);
t_list		**get_all(char	*line);
char		*add_str(char *str, char *str2);
char		*get_lines(int fd);
char		*new_readline(char *prev_line, char *str);
int			in_quote(char *str, int index);
int			count_words_not_in_quote(char *s, char c);
int			is_only_space(char *str);
/*Parse and split utils*/
void		free_aastring(char ***str);
void		put_aastring(char ***str);
size_t		ft_astrlen(char **str);
size_t		ft_aastrlen(char ***astr);
void		free_alist(t_list **alst);
char		*str_to_chr(char *str, char c);
void		rm_heredoc(t_list *lst, int i);
void		rm_heredocs(t_list **lst);
void		update_string_hd(t_list *lst, int i);
t_list		**aastr_to_at_list(char ***aastr);
t_list		*get_beggining(char	*str, int i, char c);
t_list		*get_end(char *str, int i);
t_list		*get_end_hd(char *str, int i);
t_list		*astr_to_t_list(char **str);
void		replace_file_in_file_outs(t_list **lst);
void		invert(t_list *lst, t_list *lst2);
/*lst utils*/
void		put_lst(t_list	*lst);
void		put_alst(t_list **alst);
/*to good commands utils*/
int			in_squote(char *str, int index);
void		to_good_tildes(t_list **cmds, t_env_var **vars);
void		rm_external_quotes(t_list **cmds);
int			split_alst_on_space(t_list **cmds);
int			amount_lst_in_alst(t_list **alst);
int			set_good_args_data(t_list **cmds, t_to_good_args_data *d);
/*signal*/
void		sigint(int sig);
void		sigquit_process(int sig);
void		sigquit_process2(int sig);
void		sigquit(int sig);
void		intquit(int sig);

char		**get_envp(t_env_var *vars);
void		check_shlvl(t_env_var **v);

/*test*/
int			size_without_external_quote2(char *str);
char		*str_without_external_quotes2(char *str, int is_an_export);
char		*str_without_external_quotes(char *str);
#endif
