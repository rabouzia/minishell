/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:45:45 by junsan            #+#    #+#             */
/*   Updated: 2024/06/02 02:36:23 by rabouzia         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *input)
{
	// t_token_list	*token_list;
	// t_token			*tokens;
	// t_ast			*root;

	// tokens = NULL; 	
	// root = NULL;
	if (input)
	{
		// if(ft_strncmp(input, "env", 3) == 0)
		// 	print_env();
		// tokenize(input, &tokens);
		// token_list = get_token_list(tokens);
		// print_token(tokens);
		// (void)root;
		// parsing_tree(&token_list, &root);
		// print_tree(root, 10);
		// free_tree(root);
		// free(token_list);
		// free_token(tokens);
		free(input);
	}
}
