/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:39:22 by junsan            #+#    #+#             */
/*   Updated: 2024/06/12 17:12:46 by junsan           ###   ########.fr       */
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
			add_token(list, *start, *input - *start + 1);
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

static void	handle_open_subshell(\
	const char **input, int *depth, const char **start, t_token **list)
{
	if (*depth == 0)
	{
		(*input)++;
		*start = *input;
		add_token(list, "(", 1);
	}
	(*depth)++;
}

static void	handle_close_subshell(\
	const char **input, int *depth, const char **start, t_token **list)
{
	(*depth)--;
	if (*depth == 0)
	{
		while (ft_isspace(**start))
			(*start)++;
		add_token(list, *start, *input - *start);
		add_token(list, ")", 1);
		*start = *input + 1;
	}
}

static void	handle_operators_and_spaces(\
	const char **input, const char **start, t_token **list)
{
	const char	*delims;

	delims = DELIMS;
	if (ft_isspace(**input) || ft_strchr(delims, **input))
	{
		if (*input > *start)
			add_token(list, *start, *input - *start);
		if (ft_strchr(delims, **input))
		{
			if (*((*input) + 1) == **input)
			{
				add_token(list, *input, 2);
				(*input)++;
			}
			else
			{
				if (**input != '&')
					add_token(list, *input, 1);
			}
		}
		*start = *input + 1;
	}
}

void	tokenize(const char *input, t_token **tokens)
{
	const char	*start;
	char		in_quote;
	int			depth;

	start = input;
	in_quote = 0;
	depth = 0;
	while (*input)
	{
		handle_quotes(&input, &in_quote, &start, tokens);
		if (!in_quote)
		{
			if (*input == '(')
				handle_open_subshell(&input, &depth, &start, tokens);
			else if (depth > 0 && *input == ')')
				handle_close_subshell(&input, &depth, &start, tokens);
		}
		if (!in_quote && depth == 0)
			handle_operators_and_spaces(&input, &start, tokens);
		input++;
	}
	if (input > start)
		add_token(tokens, start, input - start);
}
