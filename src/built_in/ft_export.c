/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:38:01 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/13 16:18:32 by ramzerk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void sort_env(t_cmd_list *env)
// {
// }


void ft_export(t_ast *node, t_main_arg *arg)
{
	t_env *env;
	env = arg->env;
	while(env)
		env= env->next;
	if (node->right != NULL)
	
	if (ft_strchr(var,'=')) // search a = then stop
		env = add_builtin_node(var, var);
	else
		return;
}