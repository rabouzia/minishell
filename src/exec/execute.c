/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:34:10 by junsan            #+#    #+#             */
/*   Updated: 2024/06/17 14:29:07 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	traverse_tree(t_ast *node, t_info *info);

/*
static bool	process_subshell_node(t_ast *node)
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

static void	process_cmd_node(t_ast *node, t_info *info)
{
	(void)info;
	if (node->data)
		printf("cmd node data : %s\n", node->data);
}

static void	process_io_redirection_node(t_ast *node, t_info *info)
{
	info->status = handle_io_redirection(node->left, info);
	if (node->right)
		info ->status = handle_io_redirection(node->right, info);
}

static void	process_phrase_node(t_ast *node, t_info *info)
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
		// left is redir, right is args
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

static void	categorize_tree(t_ast *node, t_info *info)
{
	t_info	subshell_info;

	if (node->type == PIPE)
	{
		info->status = SUCCESS;
		if (node->right)
		{
			info->pipe_exists = true;
			info->pipe_used = true;
		}
	}
	else if (node->type == PHRASE && info->status == SUCCESS)
		process_phrase_node(node, info);
	else if (node->type == SUBSHELL && ft_strncmp(node->data, "(", 1) == 0 \
			&& info->status == SUCCESS)
	{
		init_info(&subshell_info);
		subshell_info.in_subshell = true;
		traverse_tree(node->left, &subshell_info);
		info->status = subshell_info.status;
	}
}
static void	traverse_tree(t_ast *node, t_info *info)
{
	if (node == NULL)
		return ;
	if (node->type == LOGICAL)
	{
		traverse_tree(node->left, info);
		while ((ft_strncmp(node->data, "&&", 2) && info->status == SUCCESS) || \
			(ft_strncmp(node->data, "||", 2) && info->status == FAILURE))
			traverse_tree(node->right, info);
	}
	else
	{
		categorize_tree(node, info);
		if (node->left)
			traverse_tree(node->left, info);
		if (node->right && info->in_subshell == false)
			traverse_tree(node->right, info);
	}
}

void	execute(t_ast *root)
{
	t_info	info;

	init_info(&info);
	if (backup_stdio(&info) == FAILURE)
		fd_log_error(NULL, NULL, strerror(errno));
	traverse_tree(root, &info);
	if (restore_stdio(&info) == FAILURE)
		fd_log_error(NULL, NULL, strerror(errno));
	cleanup_tmp_file();
	clear_info(&info);
}