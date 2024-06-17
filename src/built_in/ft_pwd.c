/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:59:35 by junsan            #+#    #+#             */
/*   Updated: 2024/06/17 18:57:07 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ft_pwd(t_cmd_list *env)
{
    char *print;
    size_t len = 512;

    print = NULL;
    print = getcwd(print, len);
    if (!print) {
        perror("kashell: pwd: ");
        return (FAIL);
    } else {
        printf("%s\n", print);
        free(print);
        return (SUCCESS);
    }
}
void get_pwd_from_env(t_env *env)
{
	while(env)
	{
		if (ft_strncmp(env->name, "PWD", 3) == 0)
			break;
	}
	env->pwd= env->name;
}