/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_dir_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:29:42 by junsan            #+#    #+#             */
/*   Updated: 2024/06/22 15:31:20 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(const char *path, t_env *lst)
{
	(void)lst;
	if (!path || *path == '\0')
		return (0);
	// else if (chdir(path) == -1)
	// 	return (0);
	// else
	// 	return (1);
	return (chdir(path) != -1);
}
void	list_dir(const char *dirname)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(dirname);
	if (dir == NULL)
	{
		perror("opendir");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
		printf("%s\n", entry->d_name);
	closedir(dir);
}
