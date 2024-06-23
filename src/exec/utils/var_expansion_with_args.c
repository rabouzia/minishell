/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_with_args.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:03:26 by junsan            #+#    #+#             */
/*   Updated: 2024/06/23 19:04:20 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_env_var(char *arg, t_info *info)
{
	char	*new_arg;
	t_env	*env;

	arg++;
	env = info->env;
	new_arg = NULL;
	while (env)
	{
		if ((ft_strncmp(env->name, arg, ft_strlen(arg)) == 0)
			&& (ft_strlen(arg) == ft_strlen(env->name)))
			new_arg = env->content;
		env = env->next;
	}
	if (new_arg == NULL)
		new_arg = "";
	return (ft_strdup(new_arg));
}

static char	*replace_expansion_var(t_info *info)
{
	char	*new_arg;
	int		status;

	new_arg = NULL;
	status = info->exit_status;
	if (status == 0)
		new_arg = ft_itoa(0);
	else if (status > 0)
		new_arg = ft_itoa(status);
	return (new_arg);
}

void	replace_env_vars_in_args(char **args, t_info *info)
{
	char	*new_arg;
	int		i;

	i = -1;
	while (args[++i])
	{
		new_arg = NULL;
		if (args[i][0] == '$')
		{
			if (args[i][1] == '?' && ft_strlen(args[i]) == 2)
				new_arg = replace_expansion_var(info);
			else
				new_arg = replace_env_var(args[i], info);
			if (new_arg)
			{
				free(args[i]);
				args[i] = new_arg;
			}
		}
	}
}
