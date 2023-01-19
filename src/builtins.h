/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:28:30 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/19 15:27:24 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int	ft_echo(char **argv, int argc);
int	ft_cd(char **args, int argc, t_env_var *vars);
int	ft_pwd(void);
int	ft_export(char *name, char *value, t_env_var **vars);
int	ft_unset(char *arg, t_env_var **vars);
int	ft_env(t_env_var *vars);
int	ft_exit(char **args, int argc, t_env_var **vars);

#endif