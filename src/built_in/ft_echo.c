/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:38:26 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/20 13:54:23 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to be completed


int	ft_echo(char *cmd,char **arg, t_env *list)
{
	int	i;
	(void) cmd;

	i = 2;
	if (arg[0][0] == '-' && arg[0][1] == 'n')
	{
		while (list->cmd[i])
		{
			if (list->cmd[i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);
}

// void print_echo(t_cmd_list *list)
// {
//     if (ft_echo(list->cmd))
//     {
//         ft_putstr_fd("\n", stdout);
//         ft_putstr_fd(list->cmd->next, stdout);
//     }
//     else
//     {
//         ft_putstr_fd("\n", stdout);
//         ft_putstr_fd(list->cmd->next, stdout);
//         ft_putstr_fd("\n", stdout);
//     }
// }