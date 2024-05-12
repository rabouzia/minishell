/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:40:31 by junsan            #+#    #+#             */
/*   Updated: 2023/11/14 18:03:32 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbr_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr && ++len)
		nbr /= 10;
	return (len);
}

char	*ft_itoa(int nbr)
{
	const char	*digits = "0123456789";
	char		*result;
	int			len;

	len = nbr_len(nbr);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!(result))
		return (NULL);
	result[len] = 0;
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
		result[0] = '-';
	while (nbr)
	{
		if (nbr > 0)
			result[--len] = digits[nbr % 10];
		else
			result[--len] = digits[nbr % 10 * -1];
		nbr /= 10;
	}
	return (result);
}
