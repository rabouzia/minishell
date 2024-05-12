/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:16:20 by junsan            #+#    #+#             */
/*   Updated: 2023/11/14 13:06:29 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*tmp_s1;
	unsigned char	*tmp_s2;

	tmp_s1 = (unsigned char *)s1;
	tmp_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && (tmp_s1[i] && tmp_s2[i]))
	{
		if (tmp_s1[i] != tmp_s2[i])
			break ;
		i++;
	}
	return ((tmp_s1[i] - (tmp_s2)[i]));
}
