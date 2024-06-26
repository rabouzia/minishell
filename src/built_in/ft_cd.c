/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:39:36 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/20 19:10:49 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to be completed

void	lst_swap(t_env *a)
{
	t_env *tmp;

	tmp = a->pwd;
	a->pwd = a->old_pwd;
	a->old_pwd = tmp;
}


int	ft_cd(const char *cmd, const char **args, t_env *list)
{
	printf("cmd in cd: %s\n", cmd);
	if (!args[0])
		return (change_dir("HOME", list), 1);
	if (args[1])
	{
		ft_putstr_fd("cd: too many arguments", 2);
		return 1;
	}
	if (ft_strncmp(args[0], "-", 1))
	{
		change_dir(list->old_pwd->content, list);
		lst_swap(list);
	}
	if (chdir(args[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd((char *)args[1], 2);
		return 1;
	}
	else
		change_dir(args[1], list);
	return (0);
}

// void	modify_pwd_in_env(t_env *env, char *str)
// {
// 	char	*new_pwd;
// 	char	*last_slash;

// 	if (str && *str != '\0')
// 	{
// 		new_pwd = ft_strjoin(env->pwd, str);
// 		free(env->pwd);
// 		env->pwd = new_pwd;
// 	}
// 	else
// 	{
// 		last_slash = strrchr(env->pwd, '/');
// 		if (last_slash)
// 			*last_slash = '\0';
// 	}
// }
