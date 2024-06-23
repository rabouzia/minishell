/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:56:30 by junsan            #+#    #+#             */
/*   Updated: 2024/06/23 15:29:25 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_info(t_info *info)
{
	info->status = SUCCESS;
	info->exit_status = 0;
	info->pipe_exists = false;
	info->pipe_used = false;
	info->stdin_fd = -1;
	info->stdout_fd = -1;
	info->tmp_fd = -1;
	info->in_subshell = false;
}

void	clear_info(t_info *info)
{
	if (info->stdin_fd != -1)
		close(info->stdin_fd);
	if (info->stdout_fd != -1)
		close(info->stdout_fd);
	if (info->tmp_fd != -1)
		close(info->tmp_fd);
	close(info->origin_stdin_fd);
	close(info->origin_stdout_fd);
}
