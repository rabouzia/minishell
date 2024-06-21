/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:58:55 by junsan            #+#    #+#             */
/*   Updated: 2024/06/22 22:28:54 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_child_task(char *cmd, char **args, t_info *info)
{
	char	**env;
	// int		built_in;
	// int		(*arr_built_in[8])(const char *, const char **, t_env *);

	env = (char **)list_to_array(info->env);
	if (env == NULL)
	{
		perror("Empty env");
		exit(EXIT_FAILURE);
	}
	if (info->pipe_exists)
	{
		close(info->pipe[0]);
		if (dup2(info->pipe[1], STDOUT_FILENO) == -1)
			return (fd_log_error("Dup pipe error", NULL, NULL));
	}
	// init_builtin(arr_built_in);
	// built_in = handler_builtin(cmd);
	printf("%s, %s, %s\n", args[0], args[1], args[2]);
	// if (built_in != NONE)
		// exit(arr_built_in[built_in](\
			// (const char *)cmd, (const char **)args, info->env);
	if (args[0][0] == '.' && args[0][1] == '/'
		&& execve(args[0], args, env) == -1)
		exit(125 + execve_log_error(args[0], errno));
	if (info->path)
	{
		execve(info->path, args, env);
		free(info->path);
	}
	if (execve(args[0], args, env) == -1)
		exit(126 + execve_log_error(cmd, errno));
	return (SUCCESS);
}

static int	monitor_child_task(char *cmd, pid_t pid, t_info *info)
{
	int	status;

	if (info->pipe_exists)
	{
		close(info->pipe[1]);
		if (dup2(info->pipe[0], STDIN_FILENO) == -1)
			return (fd_log_error("Dup pipe error", NULL, NULL));
	}
	if ((ft_strncmp(cmd, "./minishell", 11) == 0)
		&& (ft_strlen(cmd) == ft_strlen("./minishell")))
		disable_interrupt_signals();
	waitpid(pid, &status, 0);
	if (WTERMSIG(status) != 0)
	{
		if (WTERMSIG(status) == 2)
			printf("^C\n");
		info->exit_status = 128 + WTERMSIG(status);
	}
	else
		info->exit_status = WEXITSTATUS(status);
	set_signal_handler();
	if (info->pipe_exists)
		close(info->pipe[0]);
	return (SUCCESS);
}

static int	launch_process(char *cmd, char **args, t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (fd_log_error("fork error", NULL, NULL));
	if (pid == 0)
		exec_child_task(cmd, args, info);
	monitor_child_task(cmd, pid, info);
	return (info->exit_status);
}

static char	**prepend_cmd_and_add_spaces(const char *cmd, char **args)
{
	char	**new_args;
	int		arg_cnt;
	int		i;

	arg_cnt = 0;
	while (args[arg_cnt])
		arg_cnt++;
	new_args = (char **)malloc(sizeof(char *) * (arg_cnt + 2));
	if (!new_args)
	{
		perror("malloc error");
		return (NULL);
	}
	new_args[0] = ft_strdup(cmd);
	i = -1;
	while (++i < arg_cnt)
		new_args[i + 1] = args[i];
	new_args[arg_cnt + 1] = NULL;
	return (new_args);
}

int	dispatch_cmd(t_ast	*node, t_info *info)
{
	t_ast	*cmd_node;
	t_ast	*args_node;
	char	**args;
	char	**chunk;
	int		status;
	int		built_in;
	int		(*arr_built_in[8])(const char *, const char **, t_env *);

	cmd_node = node->left;
	args_node = node->right;
	args = NULL;
	chunk = NULL;
	info->path = NULL;
	if (get_path_type(cmd_node->data) == PATH_RELATIVE)
		info->path = get_absolute_path(cmd_node->data);
	if (args_node)
	{
		args = ft_split(args_node->data, ARR_SEP);
		remove_quotes_from_args(args);
		chunk = prepend_cmd_and_add_spaces(cmd_node->data, args);
	}
	else
		chunk = allocate_null_and_cmd_chunk(cmd_node->data);
	//printf("cmd : %s, args >> %s, %s\n", cmd_node->data, chunk[0], chunk[1]);
	init_builtin(arr_built_in);
	built_in = handler_builtin(chunk[0]);
	if (built_in != NONE && info->pipe_used == false)
		status = arr_built_in[built_in]((const char *)chunk[0], (const char **)chunk, info->env);
	else
		status = launch_process(chunk[0], chunk, info);
	free(chunk[0]);
	free(chunk);
	if (info->path)
		free(info->path);
	if (args)
		free_args(args);
	return (status);
}
