/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <alboudje@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:28:30 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/14 14:55:45 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int	ft_echo(char **args, t_env_var *vars);
int	ft_cd(char *arg, t_env_var *vars);
int	ft_pwd(void);
int	ft_export(char **args, t_env_var *vars);
int	ft_unset(char *arg, t_env_var *vars);
int	ft_env(t_env_var *vars);
int	exit(void);

#endif