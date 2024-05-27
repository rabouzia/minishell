/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:45:45 by junsan            #+#    #+#             */
/*   Updated: 2024/05/27 14:30:43 by junsan           ###   ########.fr       */
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
	token_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (!token_list)
		return ;
	input = readline("");
	if (input)
	{
		tokenize(input, &tokens);
		token_list->head = tokens;
		token_list->tail = tokens_last(tokens);
		//print_token(tokens);
		root = parsing_tree(&token_list);
		//(void)root;
		print_tree(root, 5);
		free(input);
	}
}
