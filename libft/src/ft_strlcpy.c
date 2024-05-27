/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:41:34 by junsan            #+#    #+#             */
/*   Updated: 2023/11/14 20:20:02 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (*src && i + 1 < len)
	{
		*dst++ = *src++;
		i++;
	}
	if (i < len)
		*dst = 0;
	while (*src++)
		i++;
	return (i);
}
