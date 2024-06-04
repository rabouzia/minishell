/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:38:01 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/04 23:45:30 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// to arrange so it can sort char *
t_list	*sort_list(t_list *lst)
{
	t_list	*head;
	int		tmp;

	head = lst;
	while (lst->next != NULL)
	{
		if (cmp(lst->data, lst->next->data) == 0)
		{
			tmp = lst->data;
			lst->data = lst->next->data;
			lst->next->data = tmp;
			lst = head;
		}
		else
			lst = lst->next;
	}
    lst = head;
	return (lst);
}
// UnCompleted

void sort_env(t_cmd_list *env)
{
    while()
}
