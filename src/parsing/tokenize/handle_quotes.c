/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:44:46 by junsan            #+#    #+#             */
/*   Updated: 2024/06/13 19:44:58 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(\
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
