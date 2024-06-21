/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:48:50 by junsan            #+#    #+#             */
/*   Updated: 2024/06/20 21:57:34 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_env(t_env *list)
{
	t_env	*cur;

	cur = list;
	while (cur)
	{
		printf("%s=%s\n", cur->name, cur->content);
		cur = cur->next;
	}
}
static int	check_in_env(const char *arg, t_env *list)
{
	t_env	*cur;

	cur = list;
	while (cur)
	{
		if (ft_strncmp(arg, cur->name, ft_strlen(cur->name)) == 0)
		{
			ft_putstr_fd(cur->content, 1);
			printf_env(list);
			return (0);
		}
		cur = cur->next;
	}
	return (0);
}

// UnCompleted
int	ft_env(const char *cmd, const char **args, t_env *list)
{
	(void)cmd;
	if (!args)
	{
		printf_env(list);
		return (0);
	}
	if (args[0])
	{
		if (sizeof(args) > 2)
		{
			ft_putstr_fd("ignoring non-option arguments", STDOUT_FILENO);
			printf_env(list);
		}
		else
			return (check_in_env(args[0], list));
	}
	return (0);
}

t_env	*builtin_new_node(char *name, char *content)
{
	t_env	*res;

	res = (t_env *)malloc(sizeof(t_env));
	if (!res)
		return (NULL);
	res->name = ft_strdup(name);
	res->content = ft_strdup(content);
	res->next = NULL;
	return (res);
}

void	add_builtin_node(t_env **head, char *name, char *content)
{
	t_env	*new_node;
	t_env	*cur;

	new_node = builtin_new_node(name, content);
	if (!name || !content || !new_node)
		return ;
	if (*head == NULL)
		*head = new_node;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
}

/*
char	**env_split(char const *str)
{
	char	**res;
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = 0;
	tmp = 0;
	if (!str)
		return (NULL);
	j = 1;
		if (str[i] == '=' && j > 0)
		{
			j--;
			tmp = 0;
		}
		res[j][tmp] =  str[i];
		i++;
		tmp++;
	}
	return (res);
	while (str[i])
	{
		if (str[i] == '=' && j > 0)
		{
			j--;
			tmp = 0;
		}
		res[j][tmp] =  str[i];
		i++;
		tmp++;
	}
	return (res);
}
*/

static void	env_split(const char *str, char **name, char **content)
{
	size_t	i;
	size_t	j;

	if (!str)
		return ;
	i = 0;
	j = 1;
	// tmp = 0;
	while (str[i] != '=')
		i++;
	*name = ft_strndup(str, i);
	i++;
	j = i;
	while (str[i])
		i++;
	*content = ft_strndup(str, i - j);
}

t_env	*fill_env(int ac, char **av, char **env)
{
	char	*name;
	char	*content;
	t_env	*arg;
	t_env	*tmp;
	int		i;

	(void)ac;
	(void)av;
	arg = ft_calloc(1, sizeof(t_env));
	if (!arg)
		return (NULL);
	i = -1;
	name = NULL;
	content = NULL;
	tmp = arg;
	while (env[++i])
	{
		env_split(env[i], &name, &content);
		add_builtin_node(&tmp, name, content);
		free(name);
		free(content);
	}
	arg = tmp;
	return (arg);
}
/*
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

t_env	*builtin_new_node(char *name, char *content)
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

void	fill_ft_env(t_main_arg *arg, char **str_env)
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
	env = builtin_new_node(name, content);
	tmp = env;
	i = 0;
	while (str_env[++i])
	{
		ptr_eq = strchr(str_env[i], '=');
		name = ft_strndup(str_env[i], ptr_eq - str_env[i] - 1);
		content = ft_strndup(str_env[i] + (ptr_eq - str_env[i]) + 1,
				ft_strlen(str_env[i] + (ptr_eq - str_env[i]) + 1));
		tmp->next = builtin_new_node(name, content);
		tmp = tmp->next;
	}
	arg->env = env;
}

t_main_arg	*fill_main_arg(int ac, char **av, char **env)
{
	t_main_arg	*arg;

	arg = malloc(sizeof(t_main_arg));
	arg->ac = ac;
	arg->av = av;
	fill_ft_env(arg, env);
	return (arg);
}
void	print_env(t_main_arg *arg)
{
	t_env *env;

	env = arg->env;
	while (env)
	{
		printf("%s=%s\n", env->name, env->content);
		env = env->next;
	}
}*/
