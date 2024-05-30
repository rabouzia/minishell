/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:50:55 by junsan            #+#    #+#             */
/*   Updated: 2024/05/30 08:41:39 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_flag(const char *arg)
{
	return (arg[0] == '-');
}

static size_t	get_total_arg_list_size(t_token **token)
{
	t_token	*cur;
	t_token	*prev;
	size_t	total_len;

	cur = *token;
	prev = NULL;
	total_len = 0;
	while (cur)
	{
		if (cur->type != CMD)
			break ;
		if (prev)
			total_len += ft_strlen(prev->data);
		if (cur->next)
			total_len++;
		else
		{
			*token = cur;
			return (total_len);
		}
		prev = cur;
		cur = cur->next;
	}
	*token = cur;
	return (total_len);
}

char	*arg_parsing(t_token **token)
{
	t_token	*cur;
	size_t	total_len;
	char	*data;
	char	*ptr;

	cur = *token;
	total_len = get_total_arg_list_size(token);
	data = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!data)
		return (NULL);
	ptr = data;
	while (cur)
	{
		ft_strlcpy(ptr, cur->data, ft_strlen(cur->data) + 1);
		ptr += ft_strlen(cur->data);
		if (cur->next)
		{
			*ptr = ' ';
			ptr++;
		}
		cur = cur->next;
	}
	*ptr = '\0';
	return (data);
}
