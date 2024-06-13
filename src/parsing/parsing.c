/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 10:49:14 by junsan            #+#    #+#             */
/*   Updated: 2024/06/13 19:30:06 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	parsor(t_token **token, t_ast **root, int start)
{
	if (!token || !*token)
		return (NULL);
	if (start == LOGICAL)
		return (parse_logical(token, root));
	else if (start == PIPE)
		return (parse_pipe(token, root));
	return (parse_phrase(token, root));
}

bool	parsing_tree(t_token_list **tokens, t_ast **root)
{
	t_token		*tmp;
	t_token		*token;
	int			priority;

	if (!tokens || !*tokens)
		return (NULL);
	token = (*tokens)->head;
	tmp = (*tokens)->head;
	priority = INT_MAX;
	while (tmp->next)
	{
		if ((int)tmp->type < priority)
			priority = (int)tmp->type;
		tmp = tmp->next;
	}
	return (parsor(&token, root, priority));
}
