/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:48:24 by junsan            #+#    #+#             */
/*   Updated: 2024/06/12 15:59:29 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(const char *var, t_main_arg *arg)
{
	t_env *env;
	t_env *last;

	if (!var)
	 	perror("unset");
	env = arg->env;
	last = arg->env;
	while(env != "var")
	{
		if (env->next->next != NULL)
			env = env->next;
		last = last->next;
	}
	free (last);
	env->next = NULL;
	
	// then reattach the removed node
}

	// if (unsertenv(var) != NULL)
	// 	perror("unset");
