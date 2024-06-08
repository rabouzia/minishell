/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:38:01 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/08 12:01:35 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// to arrange so it can sort char *
// t_list	*sort_list(t_list *lst)
// {
// 	t_list	*head;
// 	int		tmp;

// 	head = lst;
// 	while (lst->next != NULL)
// 	{
// 		if (cmp(lst->data, lst->next->data) == 0)
// 		{
// 			tmp = lst->data;
// 			lst->data = lst->next->data;
// 			lst->next->data = tmp;
// 			lst = head;
// 		}
// 		else
// 			lst = lst->next;
// 	}
//     lst = head;
// 	return (lst);
// }
// UnCompleted

// void sort_env(t_cmd_list *env)
// {
// }


void ft_export(char *var,main_arg *arg)
{
	t_env *env;
	env = arg->env;
	while(env)
		env= env->next;
	if (strchr(var,'='))
		env = neww_node(var);
	else
		return;
}