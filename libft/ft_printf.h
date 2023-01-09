/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:30:40 by alboudje          #+#    #+#             */
/*   Updated: 2022/11/21 12:41:18 by alboudje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
ssize_t	ft_putchar_fd(char c, int fd);
ssize_t	ft_putnbr_fd(int n, int fd);
ssize_t	ft_putnbrbase_fd(int n, char *base, int fd);
ssize_t	ft_putstr_fd(char *s, int fd);
ssize_t	ft_ullputnbrbase_fd(unsigned long long int n, char *base, int fd);
ssize_t	ft_uputnbr_fd(unsigned int n, int fd);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);

#endif