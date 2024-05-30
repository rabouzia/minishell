/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:05:45 by junsan            #+#    #+#             */
/*   Updated: 2024/05/29 18:50:38 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_node(const char *data, t_type type)
{
	t_ast	*new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	if (data)
		new_node->data = ft_strdup(data);
	new_node->type = type;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_ast	*attach_to_tree(t_ast *root, t_ast *node, int side)
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

void	free_tree(t_ast *root)
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
