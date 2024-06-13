/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:47:35 by junsan            #+#    #+#             */
/*   Updated: 2024/06/12 16:29:13 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' \
	|| c == '\f' || c == '\v');
}

bool	is_all_whitespace(const char *str)
{
	if (str == NULL)
		return (false);
	while (*str)
	{
		if (!ft_isspace((unsigned char)*str))
			return (false);
		str++;
	}
	return (true);
}

static int	is_control_character(char c)
{
	return (c < 32 || c == 127);
}

void	remove_control_characters(char *str)
{
	char *src;
	char *dst;

	src = str;
	dst = str;
	while (*src)
	{
		if (!is_control_character(*src))
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}
