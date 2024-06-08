/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:48:24 by junsan            #+#    #+#             */
/*   Updated: 2024/06/08 10:31:07 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(const char *var, main_arg *arg)
{
	t_env *env;

	env = arg->env;
	while(env != "var")
	{
		env = env->next;
	}
	free (env);
	// then reattach the removed node
}

	// if (unsertenv(var) != NULL)
	// 	perror("unset");
