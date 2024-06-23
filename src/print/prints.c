/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:49:26 by junsan            #+#    #+#             */
/*   Updated: 2024/06/13 11:23:24 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *head)
{
	if (!head)
	{
		printf("empty head\n");
		return ;
	}
	while (head)
	{
		printf("data : %s\n", head->data);
		head = head->next;
	}
}

void	print_file_list(t_file_list *file_list)
{
	int	i;

	i = -1;
	while (++i < (int)file_list->count)
		printf("file_list %d.name :  %s\n", i, file_list->names[i]);
}
