/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:59:35 by junsan            #+#    #+#             */
/*   Updated: 2024/06/11 12:34:07 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_pwd(t_cmd_list *env)
{
	char *print;
	size_t len;
	len = 512;
	print = NULL;
	print = getcwd(print, len);
	if (!print)
		perror("kashell: pwd: ");
	return (FAIL);
}
