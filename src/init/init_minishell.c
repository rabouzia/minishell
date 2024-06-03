/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:24:08 by junsan            #+#    #+#             */
/*   Updated: 2024/05/29 16:40:44 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	show_ascii(void)
{
	char	*line;
	int		fd;

	fd = open(ASCII_ART_PATH, O_RDONLY);
	while ("kashell")
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

	show_ascii();
	tty = ttyname(STDIN_FILENO);
	if (tty)
		printf("The current terminal for this process is: %s\n", tty);
	else
		printf("No terminal associated with this process.\n");
}