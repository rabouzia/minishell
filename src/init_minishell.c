/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:24:08 by junsan            #+#    #+#             */
/*   Updated: 2024/05/25 22:44:57 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_ascii(void)
{
	char	*line;
	int		fd;

	fd = open(ASCII_ART_PATH, O_RDONLY);
	while ("minishell")
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd);
}

void	init_minishell(void)
{
	char	*tty;
	char	*home_dir;

	show_ascii();
	home_dir = getenv("HOME");
	tty = ttyname(STDIN_FILENO);
	if (tty)
		printf("The current terminal for this process is: %s\n", tty);
	else
		printf("No terminal associated with this process.\n");
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
}

void	display_prompt(void)
{
	char	cwd[MAX_PATH_LENGTH];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("[%s]$ ", cwd);
	else
	{
		perror("getcwd");
		exit(EXIT_FAILURE);
	}
}
