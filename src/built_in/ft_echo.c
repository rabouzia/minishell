/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:38:26 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/04 23:45:13 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// to be completed


int	ft_echo(t_cmd_list *list)
{
	int	i;

	i = 2;
	if (list->cmd[0] == '-' && list->cmd[1] == 'n')
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

void print_echo(t_cmd_list *list)
{
    if (ft_echo(list->cmd))
    {
        ft_putstr_fd("\n", STDOUT);
        ft_putstr_fd(list->cmd->next, STDOUT);
    }
    else
    {
        ft_putstr_fd("\n", STDOUT);
        ft_putstr_fd(list->cmd->next, STDOUT);
        ft_putstr_fd("\n", STDOUT);
    }
}