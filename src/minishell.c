/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:14:21 by junsan            #+#    #+#             */
/*   Updated: 2024/05/29 16:41:04 by junsan           ###   ########.fr       */
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
	(void)ac;
	(void)av;
	init_minishell();
	set_signal_handler();
	while ("Kashell")
	{
		process_input();
	}
	return (0);
}
