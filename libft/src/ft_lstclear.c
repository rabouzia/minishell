/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:50:47 by junsan            #+#    #+#             */
/*   Updated: 2023/11/14 15:25:40 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*n;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		n = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = n;
	}
	*lst = NULL;
}
