/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 22:24:56 by junsan            #+#    #+#             */
/*   Updated: 2024/06/21 12:51:17 by junsan           ###   ########.fr       */
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

int	calculate_depth(const char *str)
{
	int	depth;
	int	max_depth;

	depth = 0;
	max_depth = 0;
	while (*str)
	{
		if (*str == '(')
		{
			depth++;
			if (depth > max_depth)
				max_depth = depth;
		}
		else if (*str == ')')
			depth--;
		str++;
	}
	return (max_depth);
}

void	remove_outer_parentheses(char **str, t_ast **root)
{
	int		len;
	int		depth;

	len = ft_strlen(*str);
	depth = calculate_depth(*str);
	if (depth > 1 && len >= 2 && (*str)[0] == '(' && (*str)[len - 1] == ')')
	{
		ft_memmove(*str, *str + 1, len - 2);
		(*str)[len - 2] = '\0';
		*root = new_node("(", SUBSHELL);
	}
}
