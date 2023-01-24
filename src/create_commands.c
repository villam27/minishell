/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:45:16 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/24 17:25:46 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	amount_fd(t_list **lst)
{
	t_list	**tmp;
	t_list	*tmp2;
	int		i;
	int		res;

	i = 0;
	res = 0;
	tmp = lst;
	while (tmp[i])
	{
		tmp2 = tmp[i];
		while (tmp2)
		{
			res += ((((char *)(tmp2->content))[0] == 7)
					|| (((char *)(tmp2->content))[0] == 10)
					|| (((char *)(tmp2->content))[0] == 8));
			tmp2 = tmp2->next;
		}
		i++;
	}
	return (res);
}

int	is_in_int(int lst, int a, int b, int c)
{
	return ((lst == a) || (lst == b) || (lst == c));
}

int	open_adequatly(char *file_name, int way)
{
	int	fd;

	if (way == -7)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (way == -8)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (way == -10)
		fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (fd);
}

int	*open_fds(t_list **lst)
{
	int		*fds;
	t_list	**tmp;
	t_list	*tmp2;
	int		i;
	int		j;

	fds = malloc(sizeof(int) * amount_fd(lst));
	if (!fds)
		return (NULL);
	tmp = lst;
	i = 0;
	j = 0;
	while (tmp[i])
	{
		tmp2 = tmp[i];
		while (tmp2)
		{
			if (is_in_int(((char *)(tmp2->content))[0], -7, -8, -10))
			{
				fds[j++] = open_adequatly(tmp2->next->content,
						((char *)(tmp2->content))[0]);
			}
			tmp2 = tmp2->next;

		}
		i++;
	}
	return (fds);
}

t_commands	*create_commands(t_list **lst, t_env_var *vars)
{
	t_commands	*cmds;
	int			*fds;

	(void) vars;
	cmds = NULL;
	if (lst)
		fds = open_fds(lst);
	return (cmds);
	return (NULL);
}
