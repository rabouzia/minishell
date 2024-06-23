/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:14:21 by junsan            #+#    #+#             */
/*   Updated: 2024/06/23 12:25:00 by junsan           ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*input;

	(void)ac;
	(void)av;
	env = NULL;
	init_minishell(envp, &env);
	set_signal_handler();
	if (env == NULL)
		exit(1 + printf("Fatal error: initialization failed."));
	if (increment_shlvl(env) == FAILURE)
		exit(1 + printf("Fatal error: initialization failed."));
	while (1)
	{
		input = readline("kashell$> ");
		if (!input)
			break ;
		if (!*input)
			continue ;
		else
			add_history(input);
		process_input(input, env);
	}
	clear_env(env);
	return (0);
}
