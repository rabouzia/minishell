/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pratt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:31:36 by junsan            #+#    #+#             */
/*   Updated: 2024/05/27 14:27:50 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*parse_primary(t_token **tokens)
{
	t_token	*token;
	t_cmd	*node;

	token = *tokens;
	*tokens = (*tokens)->next;
	node = new_tree(token);
	return (node);
}

t_cmd	*parse_expression(t_token **tokens, int min_binding_power)
{
	t_cmd	*left;
	t_cmd	*right;
	t_cmd	*new_node;
	t_token	*token;

	if (!tokens || !*tokens)
		return (NULL);
	left = parse_primary(tokens);
	if (!left)
		return (NULL);
	token = NULL;
	while (*tokens)
	{
 		//printf("token >> data : %s\n", (*tokens)->data);
		if ((int)(*tokens)->binding_power[0] < min_binding_power)
			break ;
		token = *tokens;
		*tokens = (*tokens)->next;
		right = parse_expression(tokens, (int)(*tokens)->binding_power[1]);
		new_node = new_tree(token);
		new_node->left = left;
		new_node->right = right;
		left = new_node;
	}
	return (left);
}
