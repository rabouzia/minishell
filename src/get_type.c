/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:49:23 by junsan            #+#    #+#             */
/*   Updated: 2024/05/27 15:52:18 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	islogical_operator(const char *token)
{
	return (ft_strncmp(token, "&&", 2) == 0 || \
		ft_strncmp(token, "||", 2) == 0);
}

bool	ispipe_operator(const char *token)
{
	return (ft_strncmp(token, "|", 1) == 0 && ft_strncmp(token, "||", 2) != 0);
}

bool	isredirection_operator(const char *token)
{
	return (ft_strncmp(token, "<", 1) == 0 || \
			ft_strncmp(token, ">", 1) == 0 || \
			ft_strncmp(token, ">>", 2) == 0 || \
			ft_strncmp(token, "<<", 2) == 0);
}

bool	issubshell_operator(const char *token)
{
	return (ft_strncmp(token, "(", 1) == 0 || ft_strncmp(token, ")", 1) == 0);
}

t_type	get_node_type(const char *data)
{
	if (islogical_operator(data))
		return (LOGICAL);
	if (ispipe_operator(data))
		return (PIPE);
	if (isredirection_operator(data))
		return (REDIRECTION);
	if (issubshell_operator(data))
		return (SUBSHELL);
	return (CMD);
}
