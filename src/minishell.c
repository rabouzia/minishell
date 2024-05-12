/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:14:21 by junsan            #+#    #+#             */
/*   Updated: 2024/05/25 13:25:46 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum)
{
	printf("Received signal: %d\n", signum);
	exit(signum);
}

void	set_signal_handler(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

/* 
Thinking !! : 
1 case. gettenv variable by env argument in main fuction  and putting them in struct
2 case. or just env variable by function, getenv()
----------------------------------------------------------
*/
	//initialization minitshell and set signal handler
	init_minishell();
	set_signal_handler();
	//working prompt and getting input in Loop
	while (true)
	{
		continue;
		//process_input();
	}
	return (0);
}
