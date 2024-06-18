/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:59:35 by junsan            #+#    #+#             */
/*   Updated: 2024/06/18 14:14:25 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_pwd(char **cmd, t_cmd_list *list)
{
	char	*print;
	size_t	len;

	len = 512;
	print = NULL;
	print = getcwd(print, len);
	if (!print)
	{
		perror("kashell: pwd: ");
		return (FAIL);
	}
	else
	{
		printf("%s\n", print);
		free(print);
		return (SUCCESS);
	}
}

void	get_pwd_from_env(t_env *env)
{
	while (env)
	{
		if (strncmp(env->name, "PWD", 4) == 0)
		{
			env->pwd = env->name + 4;
			return ;
		}
		env = env->next;
	}
	env->pwd = NULL;
}