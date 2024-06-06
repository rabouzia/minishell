/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:21:22 by rabouzia          #+#    #+#             */
/*   Updated: 2024/06/06 18:42:15 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t i;
	size_t len;
	char *str;

	if (!src || !n)
		return (NULL);
	i = 0;
	len = ft_strlen(src);
	if (len > n)
		len = n;
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	while (src[i] && n > 0)
	{
		str[i] = src[i];
		i++;
		n--;
	}
	str[i] = '\0';
	return (str);
}