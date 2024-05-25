/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:39:22 by junsan            #+#    #+#             */
/*   Updated: 2024/05/25 22:56:00 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_token **head, const char *start, size_t len)
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
/*
static void	print_token(t_token *head)
{
	while (head)
	{
		printf("data : %s\n", head->data);
		head = head->next;
	}
}
*/
static bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' \
	|| c == '\f' || c == '\v');
}

static const char	*tokenize_operator(t_token **head, const char *str)
{
	const char	*delims;
	char		*start;

	delims = DELIMS;
	start = (char *)str;
	while (*delims)
	{
		if (*(str + 1) == *str || (*str == *delims && *(str + 1) == *delims))
		{
			add_token(head, str, 2);
			str++;
			return (str);
		}
		else
		{
			add_token(head, str, 1);
			return (str);
		}
		str = start;
		delims++;
	}
	return (str);
}

t_token	*tokenize(const char *input)
{
	t_token		*head;
	const char	*start;

	start = input;
	head = NULL;
	while (*input)
	{
		if (ft_isspace(*input) || ft_strchr(DELIMS, *input))
		{
			if (input > start)
				add_token(&head, start, input - start);
			if (ft_strchr(DELIMS, *input))
				input = tokenize_operator(&head, input);
			start = input + 1;
		}
		input++;
	}
	if (input > start)
		add_token(&head, start, input - start);
	return (head);
}
