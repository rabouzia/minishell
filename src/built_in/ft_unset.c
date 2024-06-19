/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:48:24 by junsan            #+#    #+#             */
/*   Updated: 2024/06/19 14:04:59 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **cmd, t_cmd_list *list)
{
	t_env *env;
	t_env *last;

	if (!cmd)
	 	perror("unset");
	env = list->env;
	last = list->env;
	while(env)
	{
		if (env->next->next != NULL)
			env = env->next;
		last = last->next;
	}
	free (last);
	env->next = NULL;
	return 0;
}

	// if (unsertenv(var) != NULL)
	// 	perror("unset");
