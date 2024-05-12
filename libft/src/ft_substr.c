/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:42:06 by junsan            #+#    #+#             */
/*   Updated: 2023/11/14 17:58:59 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*new;

	if (!str)
		return (NULL);
	if (ft_strlen(str) < start)
		len = 0;
	if (ft_strlen(str + start) < len)
		len = ft_strlen(str + start);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, str + start, len + 1);
	return (new);
}
