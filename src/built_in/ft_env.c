/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:48:50 by junsan            #+#    #+#             */
/*   Updated: 2024/06/04 23:45:21 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// UnCompleted
bool	my_env(t_cmd_list *env)
{
	while (env != NULL)
	{
		if (ft_strchr(env->cmd, '='))
			printf("%s\n", env->cmd);
		env = env->next;
	}
	return (SUCCESS);
}
