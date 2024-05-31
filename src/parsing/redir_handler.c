/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:41:02 by junsan            #+#    #+#             */
/*   Updated: 2024/05/31 20:19:17 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_input_redirection(const char *data)
{
	return (ft_strncmp(data, "<", 1) == 0);
}

bool	is_output_redirection(const char *data)
{
	return (ft_strncmp(data, ">", 1) == 0 || ft_strncmp(data, ">>", 2) == 0);
}

bool	is_append_redirection(const char *data)
{
	return (ft_strncmp(data, ">>", 2) == 0);
}

bool	is_heredoc_redirection(const char *data)
{
	return (ft_strncmp(data, "<<", 2) == 0);
}
