/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:38:01 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/12 17:42:29 by rabouzia         ###   ########.fr       */
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

char	**env_split(char const *str, char c)
{
	char		**str_arr;
	size_t		i;
	size_t		j;
	size_t		tmp;

	if (!str)
		return (NULL);
	str_arr = (char **)malloc(sizeof(char *) * (count_word(str, c) + 1));
	if (!str_arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count_word(str, c) && str[j])
	{
		while (str[j] == c)
			j++;
		tmp = j;
		while ((str[j] != c) && str[j])
			j++;
		str_arr[i] = ft_strdup_result(&((char *)str)[tmp], j - tmp);
		if (!str_arr[i++])
			ft_free(str_arr);
	}
	str_arr[i] = NULL;
	return (str_arr);
}

void ft_export(char *var, t_main_arg *arg)
{
	t_env *env;
	env = arg->env;
	while(env)
		env= env->next;
	if (strchr(var,'=')) // search a = then stop
		env = builtin_new_node(var, var);
	else
		return;
}