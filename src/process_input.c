/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:45:45 by junsan            #+#    #+#             */
/*   Updated: 2024/05/26 09:49:11 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(void)
{
	t_token	*tokens;
	char	*input;

	tokens = NULL;
	input = readline("");
	if (input)
	{
		tokens = tokenize(input);
		(void)tokens;
		free(input);
	}
}
