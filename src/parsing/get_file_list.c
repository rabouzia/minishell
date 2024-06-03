/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:17:41 by junsan            #+#    #+#             */
/*   Updated: 2024/06/01 11:15:20 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_file_list(t_file_list *file_list)
{
	int	i;

	if (file_list == NULL)
		return ;
	i = -1;
	while (++i < (int)file_list->count)
		free(file_list->names[i]);
	free(file_list->names);
	free(file_list);
}

const char	*get_path(const char *full_path)
{
	const char	*file_name;
	char		*path;
	size_t		path_len;

	file_name = ft_strchr(full_path, '/');
	if (file_name == NULL)
		return (ft_strdup("."));
	path_len = file_name - full_path + 1;
	path = (char *)malloc(sizeof(char) * (path_len + 1));
	if (path == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	ft_strlcpy(path, full_path, path_len + 1);
	path[path_len] = '\0';
	return ((const char *)path);
}

t_file_list	*get_file_list(const char *path)
{
	t_file_list		*file_list;
	DIR				*dir;
	int				file_count;

	file_list = (t_file_list *)malloc(sizeof(t_file_list));
	if (file_list == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	file_count = get_file_list_size(path);
	if (file_count == 0)
	{
		file_list->names = NULL;
		file_list->count = 0;
		return (file_list);
	}
	else if (file_count < 0)
		return (NULL);
	dir = get_dir(path, file_count, &file_list);
	return (get_entry_list(file_list, dir));
}
