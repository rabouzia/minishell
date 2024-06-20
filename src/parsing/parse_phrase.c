/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_phrase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:24:59 by junsan            #+#    #+#             */
/*   Updated: 2024/06/19 14:18:21 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// what to do : cmd(left) + flag(right)
// or echo "something"
static bool	parse_cmd(t_token **token, t_ast **node)
{
	t_ast	*cmd_node;
	char	*arg_tokens;

	printf("cmd >> \n");
	printf("token cmd : %s\n", (*token)->data);
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
			arg_tokens = arg_parsing(token);
			cmd_node->right = new_node(arg_tokens, ARGS);
			free(arg_tokens);
		}
		*node = cmd_node;
	}
	return (true);
}

// case : [<in1 cmd1 in2>]
static void	parse_redirection_part(\
			t_token **token, t_ast **phrase_node, t_ast **node)
{
	t_ast	*left;
	t_ast	*right;

	left = NULL;
	right = NULL;
	if (*token && (*token)->type == REDIRECTION)
	{
		parse_redirection(token, &left);
		(*phrase_node)->left = left;
		if (*token && (*token)->type == CMD)
		{
			parse_cmd(token, &right);
			(*phrase_node)->right = right;
			parse_io_redirection(token, &(left->right));
		}
		else if (*token && (*token)->type == SUBSHELL)
		{
			parse_subshell(token, &right);
			(*phrase_node)->right = right;
			parse_io_redirection(token, &(left->right));
		}
		*node = *phrase_node;
	}
}

// cose : [cmd1 < in2] or [cmd1 > in2]
static void	parse_cmd_part(t_token **token, t_ast **phrase_node, t_ast **node)
{
	t_ast	*left;

	left = NULL;
	parse_cmd(token, node);
	if (*token && (*token)->type == REDIRECTION)
	{
		parse_redirection(token, &left);
		(*phrase_node)->left = left;
	}
	(*phrase_node)->right = *node;
	*node = *phrase_node;
}

bool	parse_phrase(t_token **token, t_ast **node)
{
	t_ast	*phrase_node;

	printf("pharse >> \n");
	phrase_node = new_node(NULL, PHRASE);
	if (!phrase_node)
		return (false);
	parse_subshell(token, node);
	if (*token && (*token)->type == REDIRECTION)
		parse_redirection_part(token, &phrase_node, node);
	else if (*token && (*token)->type == CMD)
		parse_cmd_part(token, &phrase_node, node);
	return (true);
}
