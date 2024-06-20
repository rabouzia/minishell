/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:39:36 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/20 14:02:58 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to be completed

in

void	lst_swap(t_cmd_list *a)
{
	t_cmd_list	*tmp;

	tmp = a->env->pwd;
	a->env->pwd = a->env->old_pwd;
	a->env->old_pwd = tmp;
}

int	ft_cd(char *cmd, char **arg, t_env *list)
{
	if (!arg[1])
		return (change_dir("HOME", list), 1);
	if (arg[2])
	{
		ft_putstr_fd("cd: too many arguments", 2);
		return (1);
	}
	if (ft_strncmp(arg[1], "-", 1))
	{
		change_dir(list->old_pwd->content, list);
		lst_swap(list);
	}
	if (chdir(arg[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(arg[1], 2);
		return (1);
	}
	else
		change_dir(cmd[1], list);
	return (0);
}
