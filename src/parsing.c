/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:49:14 by junsan            #+#    #+#             */
/*   Updated: 2024/05/27 14:44:13 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	attach_to_tree_left(t_cmd **root, t_cmd *new_node)
{
	t_cmd	*tmp;

	if (!*root)
		*root = new_node;
	else
	{
		tmp = *root;
		while (tmp->left && tmp->left->type == LOGICAL)
			tmp = tmp->left;
		tmp->left = new_node;
	}
}
*/

static void	handle_cmd_node(t_token *token, t_cmd **cur)
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

static void	handle_logical_operator(t_token **token, t_cmd **cur, t_cmd **root, bool *up_down_flag)
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

static void	handle_pipe_operator(t_token **token, t_cmd **cur, t_cmd **root, bool *up_down_flag)
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

static void	handle_redirection_operator(t_token **token, t_cmd **cur, t_cmd **root, bool *up_down_flag)
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

t_cmd	*parsing_tree(t_token_list **tokens)
{
	t_cmd	*root;
	t_cmd	*cur;
	t_token	*token;
	bool	up_down_flag;

	if (!tokens || !*tokens)
		return (NULL);
	root = NULL;
	cur = NULL;
	up_down_flag = true;
	token = (*tokens)->head;
	while (token)
	{
		printf("token >> data : %s\n", token->data);
		if (token->type == REDIRECTION)
			handle_redirection_operator(&token, &cur, &root, &up_down_flag);
		else if (token->type == LOGICAL)
			handle_logical_operator(&token, &cur, &root, &up_down_flag);
		else if (token->type == PIPE)
			handle_pipe_operator(&token, &cur, &root, &up_down_flag);
		else if (token->type == CMD)
			handle_cmd_node(token, &cur);
		token = token->next;
	}
	if (root)
		return (root);
	return (cur);
}
