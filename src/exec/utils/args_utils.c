/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:48:46 by junsan            #+#    #+#             */
/*   Updated: 2024/06/23 15:29:40 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	clear_flag(char **str, int idx)
{
	int	i;

	i = -1;
	while (++i < idx)
		free(str[i]);
	free(str);
}

static char **split_flags(const char *flags)
{
	size_t 	len;
	int		idx;
	int		i;
	char	**res;

	len = ft_strlen(flags);
	res = (char **)malloc(sizeof(char *) * (len * 2 + 1));
	if (res == NULL)
	{
		perror("malloc error");
		return (NULL);
	}
	idx = -1;
	i = = 1;
	while (++i < (int)len)
	{
		res[++idx] = (char *)malloc(sizeof(char) * 3);
		if (res[idx] == NULL)
		{
			perror("malloc error");
			clear_flag(str, idx);
			return (NULL);
		}
	}
	res[idx] = NULL;
	return (res);
}
*/
void	free_args(char **args)
{
	int	i;

	i = -1;
	if (args)
	{
		while (args[++i])
			free(args[i]);
		free(args);
	}
}

char	**allocate_null_and_cmd_chunk(const char *cmd)
{
	char	**chunk;

	chunk = (char **)malloc(sizeof(char *) * 2);
	if (chunk == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	chunk[0] = ft_strdup(cmd);
	chunk[1] = NULL;
	return (chunk);
}

void	remove_quotes_from_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		remove_quotes(args[i]);
}

void	replace_env_vars_in_args(char **args, t_info *info)
{
	t_env	*env;
	char	*new_arg;
	char	*str;
	char	*status;
	int		i;

	i = -1;
	new_arg = NULL;
	status = NULL;
	while (args[++i])
	{
		env = info->env;
		if (args[i][0] == '$')
		{
			str = args[i];
			str++;
			if (str[0] == '?' && ft_strlen(str) == 1)
				status = ft_itoa(info->exit_status);
			while (env)
			{
				if (ft_strncmp(env->name, str, ft_strlen(str)) == 0
					&& ft_strlen(str) == ft_strlen(env->name))
					new_arg = env->content;
				env = env->next;
			}
			if (new_arg == NULL)
				new_arg = "";
			free(args[i]);
			args[i] = ft_strdup(new_arg);
			if (status[0] == '0')
			{
				free(args[i]);
				args[i] = ft_itoa(0);
			}
			else
			{
				free(args[i]);
				args[i] = status;
			}
		}
	}
}
