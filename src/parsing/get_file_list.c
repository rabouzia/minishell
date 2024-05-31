/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:17:41 by junsan            #+#    #+#             */
/*   Updated: 2024/05/31 20:19:11 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_file_list(t_file_list *file_list)
{
	int	i;

	if (file_list == NULL)
		return ;
	i = -1;
	while (++i < file_list->count)
		free(file_list->names[i]);
	free(file_list->names);
	free(file_list);
}

static int	get_file_list_size(const char *path)
{
	int	file_count;
	DIR	*dir;

	file_coutn = 0;
	dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		return (-1);
	}
	while (dir)
	{
		if (ft_strncmp(entry->d_name, ".", 1) != 0 && \
			ft_strncmp(entry->d_name, "..", 2) != 0)
			file_count++;
	}
	closedir(dir);
	return (file_count);
}

static void	get_empty_list(t_file_list **empty_list)
{
	(*empty_list)->names = NULL;
	(*empty_list)->count = 0;
}

static t_file_list	*get_entry_list(t_file_list *file_list, DIR	*dir)
{
	int	i;
	int	index;

	index = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, ".", 1) != 0 && \
			ft_strncmp(entry->d_name, "..", 2) != 0)
		{
			file_list->names[index] = ft_strdup(entry->d_name);
			if (file_list->names[index] == NULL)
			{
				perror("strdup");
				file_list->count = index - 1;
				free_file_list(file_list);
				closedir(dir);
				return (NULL);
			}
			index++;
		}
		entry = opendir(dir);
	}
	closedir(dir);
	return (file_list);
}

static DIR	*get_dir(const char *path, int file_count, t_file_list **file_list)
{
	DIR	*dir;

	(size_t)file_count;
	dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	(*file_list)->names = (char **)malloc(sizeof(char *) * file_count);
	if (file_list->names == NULL)
	{
		perror("malloc");
		free(file_list);
		closedir(dir);
		return (NULL);
	}
	(*file_list)->count = file_count;
}

t_file_list	*get_file_list(const char *path)
{
	t_file_list		*file_list;
	struct dirent	*entry;
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
		return (get_empty_list(&file_list), file_list);
	else if (file_count < 0)
		return (NULL);
	dir = get_dir(path, file_count, &file_list);
	return (get_entry_list(file_list, dir));
}
