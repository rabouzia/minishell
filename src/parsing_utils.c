/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:05:45 by junsan            #+#    #+#             */
/*   Updated: 2024/05/27 15:55:20 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_tree(t_token *token)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->data = ft_strdup(token->data);
	new_node->type = token->type;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	free_tree(t_cmd *node)
{
	if (node)
	{
		free_tree(node->left);
		free_tree(node->right);
		free(node->data);
		free(node);
	}
}
