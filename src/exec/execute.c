/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:34:10 by junsan            #+#    #+#             */
/*   Updated: 2024/06/10 20:20:02 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_info(t_info *info)
{
	info->status = SUCCESS;
	info->pipe_exists = false;
	info->pipe_used = false;
	info->remainder = NULL;
	info->input_fd = -1;
	info->output_fd = -1;
	info->tmp_fd = -1;
}

static void	categorize_tree(t_ast *node, t_info *info)
{
	(void)info;
	if (node->data)
		printf("node data : %s\n", node->data);
	/*
	if (node->type == LOGICAL)
	{
		if (node->right && info->status == SUCCESS)
			printf()
	}
	if (node->type == PIPE)
	{

	}*/
}

static void	traverse_tree(t_ast *node, t_info *info)
{
	if (node == NULL)
		return ;
	if (node->type == LOGICAL)
	{
		traverse_tree(node->left, info);
		if ((ft_strncmp(node->data, "&&", 2) && info->status == SUCCESS) || \
			(ft_strncmp(node->data, "||", 2) && info->status == FAIL))
			traverse_tree(node->right, info);
	}
	else
	{
		categorize_tree(node, info);
		if (node->left)
			traverse_tree(node->left, info);
		if (node->right)
			traverse_tree(node->right, info);
	}
}

void	execute(t_ast *root)
{
	t_info	info;

	init_info(&info);
	traverse_tree(root, &info);
}
