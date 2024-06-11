/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:41:34 by junsan            #+#    #+#             */
/*   Updated: 2024/06/11 23:59:31 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst)
		return 0;
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
