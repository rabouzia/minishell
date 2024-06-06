/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:48:50 by junsan            #+#    #+#             */
/*   Updated: 2024/06/06 18:42:44 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// UnCompleted
bool	my_env(t_cmd_list *env)
{
	while (env != NULL)
	{
		if (ft_strchr(env->cmd, '='))
			printf("%s\n", env->cmd);
		env = env->next;
	}
	return (SUCCESS);
}

t_env	*neww_node(char *name, char *content)
{
	t_env	*res;

	res = malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->name = name;
	res->content = content;
	res->next = NULL;
	return (res);
}

void	fill_ft_env(main_arg *arg, char **str_env)
{
	int		i;
	t_env	*env;
	t_env	*tmp;
	char	*name;
	char	*content;
	char	*ptr_eq;

	name = NULL;
	content = NULL;
	ptr_eq = strchr(str_env[0], '=');
	name = ft_strndup(str_env[0], ptr_eq - str_env[0]);
	content = ft_strndup(str_env[0] + (ptr_eq - str_env[0]),
			ft_strlen(str_env[0] + (ptr_eq - str_env[0]) + 1));
	env = neww_node(name, content);
	tmp = env;
	i = 0;
	while (str_env[++i])
	{
		ptr_eq = strchr(str_env[i], '=');
		name = ft_strndup(str_env[i], ptr_eq - str_env[i] - 1);
		content = ft_strndup(str_env[i] + (ptr_eq - str_env[i]) + 1,
				ft_strlen(str_env[i] + (ptr_eq - str_env[i]) + 1));
		tmp->next = neww_node(name, content);
		tmp = tmp->next;
	}
	arg->env = env;
}

main_arg	*fill_main_arg(int ac, char **av, char **env)
{
	main_arg	*arg;

	arg = malloc(sizeof(main_arg));
	arg->ac = ac;
	arg->av = av;
	fill_ft_env(arg, env);
	return (arg);
}
void	print_env(main_arg *arg)
{
	t_env *env;

	env = arg->env;
	while (env)
	{
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
}