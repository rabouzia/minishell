/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:24:05 by junsan            #+#    #+#             */
/*   Updated: 2024/06/13 19:24:19 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse_pipe(t_token **token, t_ast **node)
{
	t_ast	*pipe_node;
	t_ast	*left;

	left = NULL;
	printf("pipe >> \n");
	parse_phrase(token, node);
	while (*token && (*token)->type == PIPE)
	{
		printf("token pipe : %s\n", (*token)->data);
		pipe_node = new_node((*token)->data, (*token)->type);
		if (!pipe_node)
			return (false);
		*token = (*token)->next;
		parse_phrase(token, &left);
		pipe_node->left = left;
		pipe_node->right = *node;
		*node = pipe_node;
	}
	return (true);
}
