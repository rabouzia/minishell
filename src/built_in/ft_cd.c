/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:39:36 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/18 13:59:18 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to be completed

int	ft_cd(char **cmd, t_cmd_list *list)
{
	int	size;

	if (!list->cmd || !*list->cmd)
		return (0);
	size = ft_lstsize(list);
	if (!list->cmd)
		return (printf("cd : missing arguments\n"), 2);
	if (size > 2)
		return (printf("cd too much arguments \n"), 2);
	list = list->next;
	if (size == 1 || (list->cmd[1] && strcmp(list->cmd[1], "~") == 0))
		change_dir(getenv("HOME"));
	else
		change_dir(list->cmd[1]);
	change_dir(list->cmd);
}

void	modify_pwd_in_env(t_env *env, char *str)
{
	char	*new_pwd;
	char	*last_slash;

	if (str && *str != '\0')
	{
		new_pwd = ft_strjoin(env->pwd, str);
		free(env->pwd);
		env->pwd = new_pwd;
	}
	else
	{
		last_slash = strrchr(env->pwd, '/');
		if (last_slash)
			*last_slash = '\0';
	}
}
