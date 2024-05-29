/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:45:58 by junsan            #+#    #+#             */
/*   Updated: 2024/05/29 11:48:20 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtin(int (*func[])(char **, t_cmd_list *))
{
	func[CD] = my_cd;
	func[M_ECHO] = my_echo;
	func[ENV] = my_env;
	func[EXIT] = my_exit;
	func[EXPORT] = my_export;
	func[PWD] = my_pwd;
	func[UNSET] = my_unset;
}

int	handler_builtin(const char *cmd)
{
	if (ft_strncmp(str, "cd", 3) == 0)
		return (CD);
	else if (ft_strncmp(str, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (EXIT);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (UNSET);
	else
		return (NONE);
}
