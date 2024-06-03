/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_dir_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:29:42 by junsan            #+#    #+#             */
/*   Updated: 2024/05/31 19:16:56 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(const char *path)
{
	return (chdir(path));
}

bool	get_cur_dir(void)
{
	char	cwd[MAX_PATH_LENGTH];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (SUCCESS);
	}
	else
		perror("getcwd");
	return (FAIL);
}

bool	file_exist(const char *filename)
{
	return (access(filename, F_OK) == 0);
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