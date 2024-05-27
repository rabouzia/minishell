/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:24:56 by junsan            #+#    #+#             */
/*   Updated: 2024/05/28 18:46:25 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_token(t_token *head)
{
	t_token	*node;

	if (!head)
		return ;
	while (head)
	{
		node = head->next;
		free(head->data);
		free(head);
		head = node;
	}
	head = NULL;
}
