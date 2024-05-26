/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:41:06 by junsan            #+#    #+#             */
/*   Updated: 2024/05/26 22:02:54 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_type	get_node_type(const char *data)
{
	if (islogical_operator(data))
		return (LOGICAL);
	if (ispipe_operator(data))
		return (PIPE);
	if (isredirection_operator(data))
		return (REDIRECTION);
	return (CMD);
}

void	add_token(t_token **head, const char *start, size_t len)
{
	t_token	*cur;
	t_token	*new_node;
	char	*data;

	data = (char *)malloc(sizeof(char) * (len + 1));
	data = ft_memcpy(data, start, len);
	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->data = ft_strdup(data);
	new_node->next = NULL;
	new_node->type = get_node_type(new_node->data);
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

t_token	*tokens_last(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens->next)
		tokens = tokens->next;
	return (tokens);
}

size_t	tokens_size(t_token *head)
{
	size_t	len;

	if (!head)
		return (0);
	len = 0;
	while (head)
	{
		head = head->next;
		len++;
	}
	return (len);
}

void	free_token(t_token **head)
{
	t_token	*node;

	if (!head)
		return ;
	while (*head)
	{
		node = (*head)->next;
		free((*head)->data);
		free(*head);
		*head = node;
	}
	*head = NULL;
}
