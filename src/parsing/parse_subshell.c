/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:26:43 by junsan            #+#    #+#             */
/*   Updated: 2024/06/17 16:32:54 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_subshell(t_token **token, t_ast **node)
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
		*token = (*token)->next->next;
		*node = subshell_node;
	}
	return (true);
}
