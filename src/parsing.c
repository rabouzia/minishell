/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:49:14 by junsan            #+#    #+#             */
/*   Updated: 2024/05/28 19:51:48 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parse_logical(t_token **token, t_cmd **node);

static bool	parse_cmd(t_token **token, t_cmd **node)
{
	t_cmd	*cmd_node;

	printf("cmd >> \n");
	if (*token && (*token)->type == CMD)
	{
		cmd_node = new_node(NULL, CMD);
		if (!cmd_node)
			return (NULL);
		cmd_node->left = new_node(*token, (*token)->type);
		printf("token cmd : %s\n", (*token)->data);
		*token = (*token)->next;
		if (*token)
		{
			cmd_node->right = new_node((*token), (*token)->type);
			printf("token cmd : %s\n", (*token)->data);
			*token = (*token)->next;
		}
		if (!(*token))
		{
			printf("token finish\n");
			return (true);
		}
		*node = cmd_node;
		//printf("check \n");
		//print_tree(*node, 10);
		//print_tree(*node, 5);
		// what to do : cmd(left) + flag(right)
	}
	return (true);
}

static bool	parse_subshell(t_token **token, t_cmd **node)
{
	printf("subshell >> \n");
	if (*token && (*token)->type == SUBSHELL)
	{
		parse_logical(token, node);
		*token = (*token)->next;
		if (*token == NULL || (*token)->type != SUBSHELL)
		{
			printf("Mismatched subshell\n");
			exit(EXIT_FAILURE);
		}
		*token = (*token)->next;
	}
	return (true);
}

static bool	parse_io_redirection(t_token **token, t_cmd **node)
{
	t_cmd	*io_redirection_node;
	t_cmd	*left;
	t_cmd	*right;

	right = NULL;
	printf("io_redirection >> \n");
	//parse_cmd(token, node);
	while (*token && (*token)->type == REDIRECTION)
	{
		printf("123dshdkjas");
		io_redirection_node = new_node(NULL, IO);
		if (!io_redirection_node)
			return (false);
		left = new_node(*token, (*token)->type);
		*token = (*token)->next;
		right = new_node(*token, (*token)->type);
		*token = (*token)->next;
		io_redirection_node->left = left;
		io_redirection_node->right = right;
		*node = io_redirection_node;
		parse_cmd(token, node);
		print_tree(io_redirection_node, 10);
	}
	return (true);
}

static bool	parse_redirection(t_token **token, t_cmd **node)
{
	t_cmd	*redirection_node;
	t_cmd	*left;

	left = NULL;
	printf("redirection >> \n");
	parse_subshell(token, node);
	redirection_node = new_node(NULL, REDIRECTION);
	if (!redirection_node)
		return (false);
	if ((*node)->left == NULL)
		(*node)->left = redirection_node;
	else
		(*node)->right = redirection_node;
	parse_io_redirection(token, &left);
	redirection_node->left = left;
	*node = redirection_node;
	return (true);
}

static bool	parse_pharse(t_token **token, t_cmd **node)
{
	t_cmd	*pharse_node;
	t_cmd	*right;

	right = NULL;
	printf("pharse >> \n");
	pharse_node = new_node(NULL, PHARSE);
	if (!pharse_node)
		return (false);
	*node = attach_to_tree(*node, pharse_node, LEFT);
	parse_cmd(token, &right);
	while (*token && (*token)->type == REDIRECTION)
	{
		parse_redirection(token, node);
		pharse_node->left = *node;
		pharse_node->right = right;
		*node = pharse_node;
		print_tree(*node, 5);
	}
	return (true);
}

static bool	parse_pipe(t_token **token, t_cmd **node)
{
	t_cmd	*pipe_node;
	t_cmd	*left;

	left = NULL;
	printf("pipe >> \n");
	parse_pharse(token, node);
	while (*token && (*token)->type == PIPE)
	{
		printf("token pipe : %s\n", (*token)->data);
		pipe_node = new_node(*token, (*token)->type);
		if (!pipe_node)
			return (false);
		*token = (*token)->next;
		parse_pharse(token, &left);
		pipe_node->left = left;
		pipe_node->right = *node;
		*node = pipe_node;
	}
	return (true);
}

static bool	parse_logical(t_token **token, t_cmd **node)
{
	t_cmd	*logical_node;
	t_cmd	*left;

	left = NULL;
	printf("logical >> \n");
	parse_pipe(token, node);
	while (*token && (*token)->type == LOGICAL)
	{
		logical_node = new_node(*token, (*token)->type);
		if (!logical_node)
			return (false);
		*token = (*token)->next;
		parse_pipe(token, &left);
		logical_node->left = left;
		logical_node->right = *node;
		*node = logical_node;
	}
	return (true);
}

static bool	parsor(t_token **token, t_cmd **root, int start)
{
	if (!token || !*token)
		return (NULL);
	if (start == LOGICAL)
		return (parse_logical(token, root));
	else if (start == PIPE)
		return (parse_pipe(token, root));
	return (parse_pharse(token, root));
	// 임시로 해놓은것 수정 필요
}

bool	parsing_tree(t_token_list **tokens, t_cmd **root)
{
	t_token		*tmp;
	t_token		*token;
	int			priority;

	if (!tokens)
		return (NULL);
	token = (*tokens)->head;
	tmp = (*tokens)->head;
	priority = INT_MAX;
	while (tmp->next)
	{
		if ((int)tmp->type < priority)
			priority = (int)tmp->type;
		tmp = tmp->next;
	}
	return (parsor(&token, root, priority));
}
