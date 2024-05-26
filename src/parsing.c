/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:49:14 by junsan            #+#    #+#             */
/*   Updated: 2024/05/27 00:21:31 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd_node(t_token *token, t_cmd **cur)
{
	t_cmd	*cmd_node;

	if (!token)
		return ;
	cmd_node = new_tree((const char *)token->data, token->type);
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
static void	handle_redirection_operator(t_token **token, t_cmd **cur)
{
	t_cmd	*redir_node;

	if (!token || !*token)
		return ;
	redir_node = new_tree((const char *)(*token)->data, (*token)->type);
	if (*cur)
	{
		if ((*cur)->left == NULL)
			(*cur)->left = redir_node;
		else if ((*cur)->right == NULL)
			(*cur)->right = redir_node;
	}
	*cur = redir_node;
}

static void	handle_logical_operator(t_token **token, t_cmd **cur, t_cmd **root)
{
	t_cmd	*logical_node;
	t_cmd	*tmp;

	if (!token || !*token)
		return ;
	logical_node = new_tree((const char *)(*token)->data, (*token)->type);
	if (*cur)
		logical_node->right = *cur;
	if (!*root)
		*root = logical_node;
	else if ((*root)->type == PIPE)
	{
		tmp = *root;
		logical_node->right = tmp;
		*root = logical_node;
	}
	else
	{
		tmp = *root;
		while (tmp->right && tmp->right->type != LOGICAL)
			tmp = tmp->right;
		tmp->right = logical_node;
	}
	*cur = logical_node;
}

static void	handle_pipe_operator(t_token **token, t_cmd **cur, t_cmd **root)
{
	t_cmd	*pipe_node;

	if (!token || !*token)
		return ;
	pipe_node = new_tree((const char *)(*token)->data, (*token)->type);
	if (*cur)
		pipe_node->left = *cur;
	if (!*root)
		*root = pipe_node;
	*cur = pipe_node;
}

t_cmd	*parsing_tree(t_token **tokens, t_token_list **token_list)
{
	t_cmd	*root;
	t_cmd	*cur;
	t_token	*token;

	if (!tokens || !*tokens || !token_list || !*token_list)
		return (NULL);
	root = NULL;
	cur = NULL;
	token = (*token_list)->head;
	while (token)
	{
		printf("token >> data : %s\n", token->data);
		if (token->type == REDIRECTION)
			handle_redirection_operator(&token, &cur);
		else if (token->type == LOGICAL)
			handle_logical_operator(&token, &cur, &root);
		else if (token->type == PIPE)
			handle_pipe_operator(&token, &cur, &root);
		else if (token->type == CMD)
			handle_cmd_node(token, &cur);
		token = token->next;
	}
	if (root)
		return (root);
	return (cur);
}
