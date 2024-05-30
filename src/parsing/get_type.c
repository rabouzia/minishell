/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:49:23 by junsan            #+#    #+#             */
/*   Updated: 2024/05/29 15:47:32 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	get_type(const char *data)
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
