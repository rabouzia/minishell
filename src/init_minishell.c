/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:24:08 by junsan            #+#    #+#             */
/*   Updated: 2024/05/25 13:39:41 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_ascii(void)
{
	int	fd;
	char *line;

	fd = open(ASCII_ART_PATH, O_RDONLY);
	while ("minishell")
	{
		line = get_next_line(fd);
		if (!line)
			break;
		printf("%s",line);
		free(line);
	}
	close(fd);
}

void init_minishell(void)
{
	char *home_dir = getenv("HOME");
	char cwd[MAX_PATH_LENGTH];

	if (home_dir == NULL)
	{
		printf("Home environment variable is not set.\n");
		exit(EXIT_FAILURE);
	}

	if (chdir(home_dir))
	{
		perror("chdir");
		exit(EXIT_FAILURE);
	}

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("[%s]$ ", cwd);
	else
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
	show_ascii();
}
