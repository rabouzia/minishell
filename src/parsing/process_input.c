/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:45:45 by junsan            #+#    #+#             */
/*   Updated: 2024/06/23 15:27:51 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *input, t_env *env, int *exit_status)
{
	t_token_list	*token_list;
	t_token			*tokens;
	t_ast			*root;
	bool			is_parse;

	tokens = NULL;
	root = NULL;
	if (input)
	{
		remove_outer_parentheses(&input, &root);
		tokenize(input, &tokens);
		if (!check_quotes_in_tokens(tokens))
		{
			free_token(tokens);
			*exit_status = UNCLOSED_QUOTE;
			tokens = NULL;
		}
		if (tokens)
		{
			token_list = get_token_list(tokens);
			//print_token(tokens);
			is_parse = parsing_tree(&token_list, &root);
			if (is_parse)
			{
				print_tree(root, 10);
				execute(root, env, exit_status);
			}
			else
				*exit_status = PARSE_ERROR;
			free_tree(root);
			free(token_list);
			free_token(tokens);
		}
		free(input);
	}
}
