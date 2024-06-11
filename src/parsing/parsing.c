/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:49:14 by junsan            #+#    #+#             */
/*   Updated: 2024/06/11 20:25:11 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parse_logical(t_token **token, t_ast **node);
static bool	parse_pipe(t_token **token, t_ast **node);
static bool	parse_phrase(t_token **token, t_ast **node);

static bool	parse_cmd(t_token **token, t_ast **node)
{
	t_ast	*cmd_node;
	char	*arg_tokens;

	printf("cmd >> \n");
	if (*token && (*token)->type == CMD)
	{
		arg_tokens = NULL;
		cmd_node = new_node(NULL, CMD);
		if (!cmd_node)
			return (NULL);
		cmd_node->left = new_node((*token)->data, (*token)->type);
		*token = (*token)->next;
		if (*token && (*token)->type == CMD)
		{
			printf("token cmd : %s\n", (*token)->data);
			arg_tokens = arg_parsing(token);
			cmd_node->right = new_node(arg_tokens, CMD);
			free(arg_tokens);
		}
		*node = cmd_node;
		//print_tree(*node, 10);
		// what to do : cmd(left) + flag(right)
		// or echo "something"
	}
	return (true);
}

static bool	parse_subshell(t_token **token, t_ast **node)
{
	t_token	*tokens_in_subshell;
	t_ast	*subshell_node;
	char	*data_in_subshell;

	printf("subshell >> \n");
	tokens_in_subshell = NULL;
	if (*token && (*token)->type == SUBSHELL)
	{
		subshell_node = new_node("(", SUBSHELL);
		if (!subshell_node)
			return (false);
		*token = (*token)->next;
		data_in_subshell = ft_strdup((*token)->data);
		tokenize(data_in_subshell, &tokens_in_subshell);
		parse_logical(&tokens_in_subshell, node);
		free(data_in_subshell);
		free_token(tokens_in_subshell);
		subshell_node->left = *node;
		*token = (*token)->next;
		*node = attach_to_tree(*node, new_node((*token)->data, SUBSHELL), LEFT);
		*token = (*token)->next;
		*node = subshell_node;
	}
	return (true);
}

/*
static bool	parse_subshell(t_token **token, t_ast **node)
{
	t_token	*stack;
	t_token	*top;
	t_token	*tokens_in_subshell;
	t_ast	*subshell_node;
	char	*data_in_subshell;

	printf("subshell >> \n");
	tokens_in_subshell = NULL;
	stack = NULL;
	top = NULL;
	if (*token && (*token)->type == SUBSHELL)
	{
		while (*token)
		{
			if (ft_strncmp((*token)->data, "(", 1) == 0)
			{
				subshell_node = new_node("(", SUBSHELL);
				if (!subshell_node)
					return (false);
				stack = push(stack, (*token)->data);
			}
			else if (ft_strncmp((*token)->data, ")", 1) == 0)
			{
				top = pop(&stack);
				if (top == NULL)
					return (false);
				if (top->next == NULL)
				{
					data_in_subshell = trim_first_last((*token)->data);
					tokenize(data_in_subshell, &tokens_in_subshell);
					printf("data_in_subshell : %s\n", data_in_subshell);
					parse_logical(&tokens_in_subshell, node);
					free_token(tokens_in_subshell);
					free(data_in_subshell);
				}
			}
			else
				stack = push(stack, (*token)->data);
			if (stack)
				cur = stack;
			*token = (*token)->next;
		}
		if (stack)
			return (false);
		subshell_node->left = *node;
		*node = attach_to_tree(*node, new_node(")", SUBSHELL), LEFT);
		*node = subshell_node;
	}
	return (true);
}*/

static bool	parse_io_redirection(t_token **token, t_ast **node)
{
	t_ast	*io_redirection_node;
	t_ast	*left;
	t_ast	*right;

	right = NULL;
	printf("io_redirection >> \n");
	if (*token && (*token)->type == REDIRECTION)
	{
		printf("token data : %s\n", (*token)->data);
		io_redirection_node = new_node(NULL, IO);
		if (!io_redirection_node)
			return (false);
		left = new_node((*token)->data, (*token)->type);
		*token = (*token)->next;
		if (*token && (*token)->type == CMD)
		{
			right = new_node((*token)->data, (*token)->type);
			*token = (*token)->next;
		}
		io_redirection_node->left = left;
		io_redirection_node->right = right;
		*node = io_redirection_node;
		//parse_cmd(token, node);
		//print_tree(io_redirection_node, 10);
	}
	return (true);
}

static bool	parse_redirection(t_token **token, t_ast **node)
{
	t_ast	*redirection_node;
	t_ast	*left;

	printf("redirection >> \n");
	printf("token data : %s\n", (*token)->data);
	left = NULL;
	redirection_node = new_node(NULL, REDIRECTION);
	if (!redirection_node)
		return (false);
	if (*token && (*token)->type == REDIRECTION)
	{
		parse_io_redirection(token, &left);
		redirection_node->left = left;
		*node = redirection_node;
	}
	return (true);
}

static bool	parse_phrase(t_token **token, t_ast **node)
{
	t_ast	*phrase_node;
	t_ast	*left;
	t_ast	*right;

	printf("pharse >> \n");
	left = NULL;
	right = NULL;
	phrase_node = new_node(NULL, PHRASE);
	if (!phrase_node)
		return (false);
	parse_subshell(token, node);
	if (*token && (*token)->type == REDIRECTION)
	{
		while (*token && (*token)->type == REDIRECTION && \
		(is_input_redirection(((*token)->data))|| \
		is_heredoc_redirection((*token)->data)))
		{
			parse_redirection(token, &left);
			phrase_node->left = left;
			if (*token && (*token)->type == CMD)
			{
				parse_cmd(token, &right);
				phrase_node->right = right;
				parse_io_redirection(token, &(left->right));
			}
			*node = phrase_node;
		} // case : [<in1 cmd1 in2>]
	}
	else if (*token && (*token)->type == CMD)
	{
		parse_cmd(token, node);
		if (*token && (*token)->type == REDIRECTION)
		{
			parse_redirection(token, &left);
			phrase_node->left = left;
		}
		phrase_node->right = *node;
		*node = phrase_node;
	} // cose : [cmd1 < in2] or [cmd1 > in2]
	return (true);
}

static bool	parse_pipe(t_token **token, t_ast **node)
{
	t_ast	*pipe_node;
	t_ast	*left;

	left = NULL;
	printf("pipe >> \n");
	parse_phrase(token, node);
	while (*token && (*token)->type == PIPE)
	{
		printf("token pipe : %s\n", (*token)->data);
		pipe_node = new_node((*token)->data, (*token)->type);
		if (!pipe_node)
			return (false);
		*token = (*token)->next;
		parse_phrase(token, &left);
		pipe_node->left = left;
		pipe_node->right = *node;
		*node = pipe_node;
	}
	return (true);
}

static bool	parse_logical(t_token **token, t_ast **node)
{
	t_ast	*logical_node;
	t_ast	*left;

	left = NULL;
	printf("logical >> \n");
	parse_pipe(token, node);
	while (*token && (*token)->type == LOGICAL)
	{
		logical_node = new_node((*token)->data, (*token)->type);
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

static bool	parsor(t_token **token, t_ast **root, int start)
{
	if (!token || !*token)
		return (NULL);
	if (start == LOGICAL)
		return (parse_logical(token, root));
	else if (start == PIPE)
		return (parse_pipe(token, root));
	return (parse_phrase(token, root));
	// 임시로 해놓은것 수정 필요
}

bool	parsing_tree(t_token_list **tokens, t_ast **root)
{
	t_token		*tmp;
	t_token		*token;
	int			priority;

	if (!tokens || !*tokens)
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
