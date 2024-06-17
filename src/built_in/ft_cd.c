/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 02:39:36 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/17 18:55:40 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to be completed

int	ft_cd(t_cmd_list *list, t_env *env)
{
	if (!list->cmd || !*list->cmd)
		return (0);
	while (list->cmd)
	{
		if (!list->cmd)
			return (printf("cd : missing arguments\n"), 2);
		if (list->cmd > 2)
			return (printf("cd too much arguments \n"), 2);
		list->cmd = list->cmd->next;
	}
	change_dir(list->cmd);
}

void modify_pwd_in_env(t_env *env, char *str)
{
	// if cd dir
	ft_strjoin(env->pwd,str);
	// else cd .. remove after the last /;
}
