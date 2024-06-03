/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:14:21 by junsan            #+#    #+#             */
/*   Updated: 2024/06/02 02:33:35 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Thinking !! :
1 case. gettenv variable by env argument in main fuction
	and putting them in struct
2 case. or just env variable by function, getenv()
----------------------------------------------------------
*/
#include "minishell.h"

int	main(int ac, char **av)
{
	char	*input;

	(void)ac;
	(void)av;
	init_minishell();
	set_signal_handler();
	while (1)
	{
		input = readline("kashell$> ");
		if (!input)
			break ;
		if (!*input)
			continue ;
		else
			add_history(input);
		process_input(input);
	}
	return (0);
}
