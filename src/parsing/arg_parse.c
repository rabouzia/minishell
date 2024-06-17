/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:50:55 by junsan            #+#    #+#             */
/*   Updated: 2024/06/16 19:09:05 by junsan           ###   ########.fr       */
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
			total_len += ft_strlen(prev->data) + 1;
		prev = cur;
		cur = cur->next;
	}
	if (prev)
		total_len += ft_strlen(prev->data);
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
	printf("token data : %s\n", cur->data);
	total_len = get_total_arg_list_size(&cur);
	data = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!data)
		return (NULL);
	ptr = data;
	cur = *token;
	while (cur && cur->type == CMD)
	{
		ft_strlcpy(ptr, cur->data, ft_strlen(cur->data) + 1);
		ptr += ft_strlen(cur->data);
		if (cur->next && cur->next->type == CMD)
		{
			*ptr = ' ';
			ptr++;
		}
		cur = cur->next;
	}
	*ptr = '\0';
	*token = cur;
	return (data);
}
