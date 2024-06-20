/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:37:49 by junsan            #+#    #+#             */
/*   Updated: 2024/06/19 13:22:39 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strndup(const char *src, size_t n)
{
	size_t i;
	size_t len;
	char *str;

	if (!src || !n)
		return (NULL);
	i = 0;
	len = ft_strlen(src);
	if (len > n)
		len = n;
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	while (src[i] && n > 0)
	{
		str[i] = src[i];
		i++;
		n--;
	}
	str[i] = '\0';
	return (str);
}

static void	env_split(const char *str, char **name, char **content)
{
	size_t	i;
	size_t	j;

	if (!str)
		return ;
	i = 0;
	j = 1;
	while(str[i] && str[i] != '=')
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

	int i = -1;
	env = NULL;
	while (envp[++i])
		add_env(&env, envp[i]);
	return (env);
}
