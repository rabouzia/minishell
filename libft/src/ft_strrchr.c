/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:11:48 by junsan            #+#    #+#             */
/*   Updated: 2023/11/13 11:48:13 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	value;
	int		len;

	value = (char)c;
	str = (char *)s;
	len = ft_strlen(s) + 1;
	while (len--)
	{
		if (str[len] == value)
			return (&str[len]);
	}
	return (NULL);
}
