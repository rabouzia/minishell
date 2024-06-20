/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:38:26 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/20 18:15:22 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to be completed


int	ft_echo(const char *cmd, const char **args, t_env *list)
{
	int	i;
	(void) cmd;
	(void) list;
	i = 2;
	if (args[0][0] == '-' && args[0][1] == 'n')
	{
		while (args[i])
		{
			if (args[0][i] != 'n')
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