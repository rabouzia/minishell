/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:37:49 by junsan            #+#    #+#             */
/*   Updated: 2023/11/14 18:11:10 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	unsigned int	i;
	unsigned char	*tmp_ptr1;
	unsigned char	*tmp_ptr2;

	tmp_ptr1 = (unsigned char *)ptr1;
	tmp_ptr2 = (unsigned char *)ptr2;
	i = 0;
	if (!n)
		return (0);
	while (n--)
	{
		if (tmp_ptr1[i] != (tmp_ptr2)[i])
			return (tmp_ptr1[i] - tmp_ptr2[i]);
		i++;
	}
	return (0);
}
