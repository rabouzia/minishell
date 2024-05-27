/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:29:28 by junsan            #+#    #+#             */
/*   Updated: 2024/05/28 15:38:10 by junsan           ###   ########.fr       */
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
	return (ft_strncmp(token, "|", 1) == 0);
}

bool	isredirection_operator(const char *token)
{
	return (ft_strncmp(token, "<", 1) == 0 || \
		ft_strncmp(token, "<<", 2) == 0 || \
		ft_strncmp(token, ">", 1) == 0 || \
		ft_strncmp(token, ">>", 2) == 0);
}

bool	issubshell_operator(const char *token)
{
	size_t	len;

	len = ft_strlen(token);
	return (token[0] == '(' && token[len - 1] == ')');
}
