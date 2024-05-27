/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:41:52 by junsan            #+#    #+#             */
/*   Updated: 2023/11/15 12:35:56 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*ans;

	if (!s1 || !set)
		return (0);
	start = (char *)s1;
	end = start + ft_strlen(s1) - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	while (start < end && ft_strchr(set, *end))
		end--;
	ans = (char *)malloc((end - start + 1) + 1);
	if (!(ans))
		return (0);
	ft_strlcpy(ans, start, (end - start + 1) + 1);
	return (ans);
}
