/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:41:06 by junsan            #+#    #+#             */
/*   Updated: 2024/05/26 10:42:13 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' \
	|| c == '\f' || c == '\v');
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

void	print_token(t_token *head)
{
	while (head)
	{
		printf("data : %s\n", head->data);
		head = head->next;
	}
}
