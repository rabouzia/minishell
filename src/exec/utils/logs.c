/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:42:56 by junsan            #+#    #+#             */
/*   Updated: 2024/06/23 15:42:39 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_log_error(char *cmd, char *arg, char *error)
{
	ft_putstr_fd("kashell$> ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error != NULL)
		ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (FAILURE);
}

int	execve_log_error(char *cmd, int error)
{
	ft_putstr_fd("kashell$> ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error == EACCES)
		ft_putstr_fd("Permission denied.\n", STDERR_FILENO);
	else if (error == ENOENT)
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("An unknown error occurred ", STDERR_FILENO);
		ft_putstr_fd("errno = ", STDERR_FILENO);
		ft_putnbr_fd(error, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (FAILURE);
}
