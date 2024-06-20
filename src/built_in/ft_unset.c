/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:48:24 by junsan            #+#    #+#             */
/*   Updated: 2024/06/20 18:14:04 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(const char *cmd, const char **args, t_env *list)
{
	t_env *cur;
	(void) cmd;

	if (!args)
	 	perror("unset");
	cur = list;
	while(cur)
	{
		// if (cur->next->next != NULL)
		// 	cur = env->next;
		cur = cur->next;
	}
	free (cur);
	// env->next = NULL;
	return 0;
}

	// if (unsertenv(var) != NULL)
	// 	perror("unset");
