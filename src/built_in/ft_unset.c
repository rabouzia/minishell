/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:48:24 by junsan            #+#    #+#             */
/*   Updated: 2024/06/20 13:57:21 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char *cmd, char **arg, t_env *list)
{
	t_env	*last;

	if (!cmd)
		perror("unset");
	last = list;
	while (list)
	{
		if (list->next->next != NULL)
			list = list->next;
		last = last->next;
	}
	free(last);
	list->next = NULL;
	return (0);
}

// if (unsertenv(var) != NULL)
// 	perror("unset");
