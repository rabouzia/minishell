/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:45:45 by junsan            #+#    #+#             */
/*   Updated: 2024/05/31 20:38:45 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(void)
{
	t_token_list	*token_list;
	t_token			*tokens;
	t_ast			*root;
	char			*input;
	t_file_list		*file_list;

	tokens = NULL;
	root = NULL;
	file_list = NULL;
	input = readline("kashell$");
	if (input)
	{
		file_list = get_file_list(".");
		print_file_list(file_list);
		tokenize(input, &tokens);
		token_list = get_token_list(tokens);
		print_token(tokens);
		(void)root;
		parsing_tree(&token_list, &root);
		print_tree(root, 10);
		free_tree(root);
		free(token_list);
		free_token(tokens);
		free(input);
	}
}
