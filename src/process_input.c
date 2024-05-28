/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:45:45 by junsan            #+#    #+#             */
/*   Updated: 2024/05/28 21:15:12 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(void)
{
	t_token_list	*token_list;
	t_token			*tokens;
	t_cmd			*root;
	char			*input;

	tokens = NULL;
	root = NULL;
	input = readline("minishell $");
	if (input)
	{
		tokenize(input, &tokens);
		token_list = get_token_list(tokens);
		print_token(tokens);
		(void)root;
		parsing_tree(&token_list, &root);
		print_tree(root, 10);
	//	free_tree(root);
		free(token_list);
		free_token(tokens);
		free(input);
	}
}
