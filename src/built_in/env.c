/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:48:50 by junsan            #+#    #+#             */
/*   Updated: 2024/06/02 02:41:25 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// InCompleted
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
