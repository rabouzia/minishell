/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramzerk <ramzerk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:14:21 by junsan            #+#    #+#             */
/*   Updated: 2024/06/13 16:12:50 by ramzerk          ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_main_arg	*arg;
	arg = NULL;

	init_minishell();
	set_signal_handler();
	arg = fill_main_arg(ac, av, env);
	while (1)
	{
		input = readline("kashell$> ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (!*input)
			continue ;
		else
			add_history(input);
		process_input(input, arg);
	}
	return (0);
}
