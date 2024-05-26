/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:49:26 by junsan            #+#    #+#             */
/*   Updated: 2024/05/26 16:15:37 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *head)
{
	if (!head)
	{
		printf("empty head\n");
		return ;
	}
	while (head)
	{
		printf("data : %s\n", head->data);
		head = head->next;
	}
}

static void	print_tree_util(t_cmd *node, int space, int depth)
{
	int	i;

	if (node == NULL)
		return ;
	space += depth;
	i = depth;
	print_tree_util(node->right, space, depth);
	printf("\n");
	while (i < space)
	{
		printf(" ");
		i++;
	}
	printf("data : %s, type : %i\n", node->data, node->type);
	print_tree_util(node->left, space, depth);
}

void	print_tree(t_cmd *root, int depth)
{
	if (!root)
		return ;
	print_tree_util(root, 0, depth);
}
