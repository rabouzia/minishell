/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:05:45 by junsan            #+#    #+#             */
/*   Updated: 2024/05/28 21:14:18 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_node(t_token *token, t_type type)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	if (token)
		new_node->data = ft_strdup(token->data);
	new_node->type = type;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_cmd	*attach_to_tree(t_cmd *root, t_cmd *node, int side)
{
	if (!root)
		root = node;
	else
	{
		if (side == LEFT)
			root->left = attach_to_tree(root->left, node, side);
		else
			root->right = attach_to_tree(root->right, node, side);
	}
	return (root);
}

void	free_tree(t_cmd *root)
{
	if (root == NULL)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	if (root->data)
		free(root->data);
	free(root);
	root = NULL;
}
