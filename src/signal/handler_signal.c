/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:06:08 by junsan            #+#    #+#             */
/*   Updated: 2024/05/29 12:45:10 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_sigint(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handler_sigquit(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
	}
	else
		ft_putstr_fd("^\\Quit: 3\n", 2);
}

static void	signal_handler(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
		handler_sigint(pid);
	else if (signo == SIGQUIT)
		handler_sigquit(pid);
}

void	set_signal_handler(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
