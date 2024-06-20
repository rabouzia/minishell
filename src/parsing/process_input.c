/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:45:45 by junsan            #+#    #+#             */
/*   Updated: 2024/06/19 12:07:22 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *input, t_env *env)
{
	// t_token_list	*token_list;
	// t_token			*tokens;
	// t_ast			*root;

	// tokens = NULL; 	
	// root = NULL;
	if (input)
  {
		remove_outer_parentheses(&input);
		tokenize(input, &tokens);
		token_list = get_token_list(tokens);
		print_token(tokens);
		parsing_tree(&token_list, &root);
		print_tree(root, 10);
		execute(root, env);
		free_tree(root);
		free(token_list);
		free_token(tokens);
		free(input);
	}
}
