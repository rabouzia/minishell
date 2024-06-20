/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:45:58 by junsan            #+#    #+#             */
/*   Updated: 2024/06/19 13:58:18 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_tab_builtins(t_cmd_list *cmd)
// {
// 	cmd->tab_func[CD] = ft_cd;
// 	cmd->tab_func[M_ECHO] = ft_echo;
// 	cmd->tab_func[ENV] = ft_env;
// 	cmd->tab_func[EXIT] = ft_exit;
// 	cmd->tab_func[EXPORT] = ft_export;
// 	cmd->tab_func[PWD] = ft_pwd;
// 	cmd->tab_func[UNSET] = ft_unset;
// }

void 	init_builtin(t_cmd_list *var)
{
	var->func[CD] = ft_cd;
	var->func[M_ECHO] = ft_echo;
	var->func[ENV] = ft_env;
	var->func[EXIT] = ft_exit;
	var->func[EXPORT] = ft_export;
	var->func[PWD] = ft_pwd;
	var->func[UNSET] = ft_unset;
	var->func[NONE] = NULL;
}

int	handler_builtin(const char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (CD);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (EXIT);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (UNSET);
	else
		return (NONE);
}
