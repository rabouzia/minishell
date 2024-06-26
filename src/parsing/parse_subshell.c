/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:26:43 by junsan            #+#    #+#             */
/*   Updated: 2024/06/25 17:24:47 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ensure_capacity(\
	char **data_in_subshell, size_t *capacity, size_t space_needed)
{
	char	*new_data;

	while (space_needed > *capacity)
	{
		*capacity *= 2;
		new_data = (char *)malloc(sizeof(char) * (*capacity));
		if (!new_data)
		{
			free(*data_in_subshell);
			*data_in_subshell = NULL;
			perror("malloc error");
			return ;
		}
		ft_strlcpy(new_data, *data_in_subshell, *capacity);
		free(*data_in_subshell);
		*data_in_subshell = new_data;
	}
}

static char	*append_data_until_subshell(\
size_t *total_len, size_t *capacity, char *data_in_subshell, t_token **token)
{
	size_t	data_len;
	size_t	space_needed;

	while (*token && (*token)->type != SUBSHELL)
	{
		space_needed = *total_len + data_len + 1;
		data_len = ft_strlen((*token)->data);
		if ((*token)->next && (*token)->next->type != SUBSHELL)
			space_needed++;
		ensure_capacity(&data_in_subshell, capacity, space_needed);
		if (data_in_subshell == NULL)
			return (NULL);
		ft_strlcat(data_in_subshell, (*token)->data, *capacity);
		*total_len += data_len;
		if ((*token)->next && (*token)->next->type != SUBSHELL)
		{
			ft_strlcat(data_in_subshell, " ", *capacity);
			(*total_len)++;
		}
		*token = (*token)->next;
	}
	return (data_in_subshell);
}

static char	*collect_data_until_subshell(t_token **token)
{
	size_t	capacity;
	size_t	total_len;
	char	*data_in_subshell;

	total_len = 0;
	capacity = MEMORY_CAPACITY;
	data_in_subshell = (char *)malloc(sizeof(char) * capacity);
	if (!data_in_subshell)
		return (NULL);
	data_in_subshell[0] = '\0';
	return (append_data_until_subshell(\
				&total_len, &capacity, data_in_subshell, token));
}

bool	parse_subshell(t_token **token, t_ast **node)
{
	t_token	*tokens_in_subshell;
	t_ast	*subshell_node;
	char	*data_in_subshell;

	// printf("subshell >> \n");
	tokens_in_subshell = NULL;
	if (*token && (*token)->type == SUBSHELL)
	{
		subshell_node = new_node("(", SUBSHELL);
		if (!subshell_node)
			return (printf("subhshell error\n"), false);
		*token = (*token)->next;
		data_in_subshell = collect_data_until_subshell(token);
		tokenize(data_in_subshell, &tokens_in_subshell);
		// print_token(tokens_in_subshell);
		parse_logical(&tokens_in_subshell, node);
		if ((*token) && (*token)->data[0] != ')')
			return (printf("subshell error\n"), false);
		free(data_in_subshell);
		free_token(tokens_in_subshell);
		subshell_node->left = *node;
		*token = (*token)->next;
		*node = subshell_node;
	}
	return (true);
}
