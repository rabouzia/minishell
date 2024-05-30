/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:50:55 by junsan            #+#    #+#             */
/*   Updated: 2024/05/29 21:01:04 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_flag(const char *arg)
{
	return (arg[0] == '-');
}

static size_t	get_total_arg_list_size(t_token **token)
{
	size_t	total_len;

	total_len = 0;
	while (*token)
	{
		if ((*token)->type != CMD)
			break ;
		total_len += ft_strlen((*token)->data);
		if ((*token)->next)
			total_len++;
		*token = (*token)->next;
	}
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
