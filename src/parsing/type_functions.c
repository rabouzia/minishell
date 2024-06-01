/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:29:28 by junsan            #+#    #+#             */
/*   Updated: 2024/06/01 11:13:22 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_logical_operator(const char *token)
{
	return (ft_strncmp(token, "&&", 2) == 0 || \
		ft_strncmp(token, "||", 2) == 0);
}

bool	is_pipe_operator(const char *token)
{
	return (ft_strncmp(token, "|", 1) == 0);
}

bool	is_redirection_operator(const char *token)
{
	return (ft_strncmp(token, "<", 1) == 0 || \
		ft_strncmp(token, "<<", 2) == 0 || \
		ft_strncmp(token, ">", 1) == 0 || \
		ft_strncmp(token, ">>", 2) == 0);
}

bool	is_subshell_operator(const char *token)
{
	size_t	len;

	len = ft_strlen(token);
	return (token[0] == '(' || token[len - 1] == ')');
}

static const char	*get_path(const char *full_path)
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

bool	is_file_name(const char *token)
{
	t_file_list	*file_list;
	const char	*path;
	bool		flag;
	int			i;

	flag = false;
	path = get_path(token);
	if (path == NULL)
		return (flag);
	file_list = get_file_list(path);
	i = -1;
	while (++i < (int)file_list->count)
	{
		if (ft_strncmp(file_list->names[i], token, ft_strlen(token)) == 0)
		{
			flag = true;
			break ;
		}
	}
	print_file_list(file_list);
	printf("token data : %s, flag : %d\n", token, flag);
	free_file_list(file_list);
	free((char *)path);
	return (flag);
}
