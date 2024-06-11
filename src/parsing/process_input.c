/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:45:45 by junsan            #+#    #+#             */
/*   Updated: 2024/06/11 20:25:19 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *input)
{
	t_token_list	*token_list;
	t_token			*tokens;
	t_ast			*root;

	tokens = NULL;
	root = NULL;
	if (input)
	{
		tokenize(input, &tokens);
		token_list = get_token_list(tokens);
		print_token(tokens);
		//(void)root;
		parsing_tree(&token_list, &root);
		print_tree(root, 10);
		execute(root);
		free_tree(root);
		free(token_list);
		free_token(tokens);
		free(input);
	}
}
