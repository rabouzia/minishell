/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:49:23 by junsan            #+#    #+#             */
/*   Updated: 2024/06/11 12:58:15 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	get_type(const char *data)
{
	if (is_logical_operator(data))
		return (LOGICAL);
	if (is_pipe_operator(data))
		return (PIPE);
	if (is_redirection_operator(data))
		return (REDIRECTION);
	if (is_subshell_operator(data))
		return (SUBSHELL);
	return (CMD);
}
