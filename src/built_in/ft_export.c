/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:38:01 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/21 20:20:47 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void sort_env(t_cmd_list *env)
// {
// }


int ft_export(const char *cmd, const char **args, t_env *list)
{
	(void) cmd;
	(void) list;
	(void) args;
	// export asdas=sadasd
	// export asdas=sadasd dfdfgfdgfd=dffsdsdf sdffds=sdffdsfd
	// export (env trier)
	// export asdsa=asdsad=asdasd


	return 0;
}

// char	**env_split(char const *str, char c)
// {
// 	char		**str_arr;
// 	size_t		i;
// 	size_t		j;
// 	size_t		tmp;

// 	if (!str)
// 		return (NULL);
// 	str_arr = (char **)malloc(sizeof(char *) * (count_word(str, c) + 1));
// 	if (!str_arr)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (i < count_word(str, c) && str[j])
// 	{
// 		while (str[j] == c)
// 			j++;
// 		tmp = j;
// 		while ((str[j] != c) && str[j])
// 			j++;
// 		str_arr[i] = ft_strdup_result(&((char *)str)[tmp], j - tmp);
// 		if (!str_arr[i++])
// 			ft_free(str_arr);
// 	}
// 	str_arr[i] = NULL;
// 	return (str_arr);
// }

// t_env	*sort_list(t_env *env)
// {
// 	t_env	*head;
// 	int		tmp;

// 	head = env;
// 	while (env->next != NULL)
// 	{
// 		if (ft_strcmp(env->name, env->next->name) == 0)
// 		{
// 			tmp = env->name;
// 			env->name = env->next->name;
// 			env->next->name = tmp;
// 			env = head;
// 		}
// 		else
// 			env = env->next;
// 	}
//     env = head;
// 	return (env);
// }

// void ft_export_show(t_env *env)
// {
// 	env = sort_list(env);
// 	while (env)
// 	{
// 		printf("%s=%s\n", env->name, env->content);
// 		env = env->next;
// 	}	
// }

/*
void ft_export_add(char *var, char **arg)
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
}*/