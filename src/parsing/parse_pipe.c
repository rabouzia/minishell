/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:24:05 by junsan            #+#    #+#             */
/*   Updated: 2024/06/25 17:00:11 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_pipe(t_token **token, t_ast **node)
{
	t_ast	*pipe_node;
	t_ast	*right;

	right = NULL;
	//printf("pipe >> \n");
	if (!parse_phrase(token, node))
		return (false);
	while (*token && (*token)->type == PIPE)
	{
		pipe_node = new_node((*token)->data, (*token)->type);
		if (!pipe_node)
			return (false);
		*token = (*token)->next;
		if (!parse_phrase(token, &right))
			return (false);
		pipe_node->right = right;
		pipe_node->left = *node;
		*node = pipe_node;
	}
	return (true);
}
