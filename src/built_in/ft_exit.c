/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:05:58 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/20 18:18:40 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(const char *cmd, const char **args, t_env *list)
{
	(void) cmd;
	(void)list;
	if (*args && !ft_isdigit(ft_atoi(args[0])))
	{
		ft_putstr_fd("kashell: exit: ", 1);
		ft_putstr_fd((char *)args[0], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(1);
	}
	if (*args && sizeof(args) > 1)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 1);
		return (0);
	}
	else
	{
		ft_putstr_fd((char *)args[0], STDERR_FILENO);
		exit(ft_atoi(args[0]));
	}
}
