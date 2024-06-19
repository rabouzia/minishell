/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:05:58 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/19 14:02:40 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **cmd, t_cmd_list *list)
{	
		if (!ft_isdigit(list->cmd[1]))
		{
			ft_putstr_fd("kashell: exit: ", 1);
			ft_putstr_fd(cmd[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
		}
		else
			ft_putstr_fd(cmd[1],2);
		exit(1);
}
