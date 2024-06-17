/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:44:23 by junsan            #+#    #+#             */
/*   Updated: 2024/06/17 16:45:35 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
bool	process_subshell_node(t_ast *node)
{
	t_info	info;

	init_info(&info);
	if (node->data)
		printf("subhshell data : %s\n", node->data);
	traverse_tree(node->left, &info);
	if (info.status == SUCCESS)
		return (SUCCESS);
	else
		return (FAILURE);
}*/

void	process_cmd_node(t_ast *node, t_info *info)
{
	(void)info;
	if (node->data)
		printf("cmd node data : %s\n", node->data);
}

void	process_io_redirection_node(t_ast *node, t_info *info)
{
	info->status = handle_io_redirection(node->left, info);
	if (node->right)
		info ->status = handle_io_redirection(node->right, info);
}

// left is redir, right is args
void	process_phrase_node(t_ast *node, t_info *info)
{
	t_ast	*redirection_node;
	t_ast	*cmd_node;

	(void)info;
	redirection_node = node->left;
	cmd_node = node->right;
	if (redirection_node)
	{
		process_io_redirection_node(redirection_node, info);
		if (redirection_node->right)
			process_cmd_node(redirection_node->right, info);
	}
	if (cmd_node)
	{
		if (cmd_node->left && cmd_node->left->type == CMD)
		{
		}
		if (cmd_node->right && cmd_node->right->type == ARGS)
		{
		}
	}
}
