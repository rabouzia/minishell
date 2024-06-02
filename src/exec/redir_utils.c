/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:20:15 by junsan            #+#    #+#             */
/*   Updated: 2024/06/10 16:33:08 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_with_mode(char *file, int mode)
{
	int	fd;

	if (mode == READ)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == WRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

/*
bool	get_direction(const chat *data)
{
	if (ft_strncmp(data, "<", 2) == 0)
	else if (ft_strncmp(data, "<<", 3) == 0)
	else if (ft_strncmp(data, ">", 2) == 0)
	else if (ft_strncmp(data, ">>", 3) == 0)
	else
		return (FAILURE);
	return (SUCCESS);
}*/
