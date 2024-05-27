/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:25:17 by junsan            #+#    #+#             */
/*   Updated: 2024/05/27 16:25:39 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cmd_node(t_token *token, t_cmd **cur)
{
	t_cmd	*cmd_node;

	if (!token)
		return ;
	cmd_node = new_tree(token);
	if (!*cur)
		*cur = cmd_node;
	else
	{
		if ((*cur)->left == NULL)
			(*cur)->left = cmd_node;
		else if ((*cur)->right == NULL)
			(*cur)->right = cmd_node;
	}
}

void	handle_logical_operator(t_token **token, t_cmd **cur, t_cmd **root, bool *up_down_flag)
{
	t_cmd	*logical_node;
	t_cmd	*tmp;
	t_cmd	*old_child;

	if (!token || !*token)
		return ;
	logical_node = new_tree(*token);
	if (*cur)
		logical_node->left = *cur;
	if (!*root)
		*root = logical_node;
	else
	{
		tmp = *root;
		while (tmp->right)
		{
			if (tmp->right->type != LOGICAL)
			{
				old_child = tmp->right;
				tmp->right = logical_node;
				logical_node->left = old_child;
				break ;
			}
			tmp = tmp->right;
		}
	}
	*up_down_flag = false;
	*cur = logical_node;
}

void	handle_pipe_operator(t_token **token, t_cmd **cur, t_cmd **root, bool *up_down_flag)
{
	t_cmd	*pipe_node;

	if (!token || !*token)
		return ;
	pipe_node = new_tree(*token);
	if (*cur && (*cur)->type == REDIRECTION)
		pipe_node->left = *cur;
	if (!*root)
		*root = pipe_node;
	else if (*root)
	{
		(*root)->right = pipe_node;
		*up_down_flag = false;
	}
	*cur = pipe_node;
}

void	handle_redirection_operator(t_token **token, t_cmd **cur, t_cmd **root, bool *up_down_flag)
{
	t_cmd	*redir_node;
	t_cmd	*tmp;

	if (!token || !*token)
		return ;
	//if (ft_strncmp((*token)->data, ">", 1) == 0)
	//	printf("token data : %s\n", (*token)->data);
	redir_node = new_tree(*token);
	if (*cur && (*cur)->type != REDIRECTION)
	{
		if ((*cur)->left == NULL)
			(*cur)->left = redir_node;
		else if ((*cur)->right == NULL && *up_down_flag)
			(*cur)->right = redir_node;
	}
	else if (*cur && (*cur)->type == REDIRECTION)
	{
		if (*up_down_flag == true)
		{
			tmp = *cur;
			redir_node->left = tmp;
		}
		else
		{
			tmp = *root;
			while (tmp->right)
				tmp = tmp->right;
			tmp->right = redir_node;
			redir_node->left = *cur;
		}
	}
	*cur = redir_node;
}
