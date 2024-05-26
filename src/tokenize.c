/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:39:22 by junsan            #+#    #+#             */
/*   Updated: 2024/05/26 10:42:24 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quotes(\
	const char **input, char *in_quote, const char **start, t_token **list)
{
	if (*in_quote)
	{
		if (**input == *in_quote)
		{
			add_token(list, *start + 1, *input - *start - 1);
			*in_quote = 0;
			*start = *input + 1;
		}
	}
	else
	{
		if (**input == '"' || **input == '\'')
		{
			if (*input > *start)
				add_token(list, *start, *input - *start);
			*in_quote = **input;
			*start = *input;
		}
	}
}

static void	handle_operators_and_spaces(\
	const char **input, const char **start, t_token **list)
{
	const char	*delims;

	delims = DELIMS;
	while (*delims)
	{
		if (ft_isspace(**input) || ft_strchr(delims, **input))
		{
			if (*input > *start)
				add_token(list, *start, *input - *start);
			if (ft_strchr(delims, **input))
			{
				if (*((*input) + 1) == **input \
					|| (**input == *delims && *((*input) + 1) == *delims))
				{
					add_token(list, *input, 2);
					(*input)++;
				}
				else
					add_token(list, *input, 1);
			}
			*start = *input + 1;
		}
		delims++;
	}
}

t_token	*tokenize(const char *input)
{
	t_token		*list;
	const char	*start;
	char		in_quote;

	start = input;
	list = NULL;
	in_quote = 0;
	while (*input)
	{
		handle_quotes(&input, &in_quote, &start, &list);
		if (!in_quote)
			handle_operators_and_spaces(&input, &start, &list);
		input++;
	}
	if (input > start && !in_quote)
		add_token(&list, start, input - start);
	print_token(list);
	return (list);
}
