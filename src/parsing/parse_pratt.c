/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pratt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:31:36 by junsan            #+#    #+#             */
/*   Updated: 2024/05/29 11:00:28 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*parse_primary(t_token **tokens)
{
	t_token	*token;
	t_ast	*node;

	token = *tokens;
	*tokens = (*tokens)->next;
	node = new_tree(token);
	return (node);
}

t_ast	*parse_expression(t_token **tokens, int min_binding_power)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*new_node;
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
