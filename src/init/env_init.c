/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:37:49 by junsan            #+#    #+#             */
/*   Updated: 2024/06/21 14:27:51 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_split(const char *str, char **name, char **content)
{
	size_t	i;
	size_t	j;

	if (!str)
		return ;
	i = 0;
	j = 1;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
	{
		*name = NULL;
		*content = NULL;
		return ;
	}
	*name = ft_strndup(str, i);
	*content = ft_strndup(str + i + 1, ft_strlen(str) - i - 1);
	if (*content == NULL)
	{
		free(*name);
		*name = NULL;
	}
}

static t_env	*new_env(const char *name, const char *content)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node || !name || !content)
		return (NULL);
	new_node->name = ft_strdup(name);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	return (new_node);
}

void	add_env(t_env **head, const char *str)
{
	t_env	*new_node;
	t_env	*cur;
	char	*name;
	char	*content;

	name = NULL;
	content = NULL;
	env_split(str, &name, &content);
	new_node = new_env(name, content);
	free(name);
	free(content);
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

void	clear_env(t_env *head)
{
	t_env	*cur;

	if (head == NULL)
		return ;
	while (head)
	{
		cur = head->next;
		free(head->name);
		free(head->content);
		free(head);
		head = cur;
	}
	head = NULL;
}

size_t	env_size(t_env *head)
{
	t_env	*cur;
	size_t	size;

	size = 0;
	cur = head;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return (size);
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	int		i;

	i = -1;
	env = NULL;
	while (envp[++i])
		add_env(&env, envp[i]);
	return (env);
}
