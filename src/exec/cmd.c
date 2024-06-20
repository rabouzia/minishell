/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:58:55 by junsan            #+#    #+#             */
/*   Updated: 2024/06/20 16:34:01 by rabouzia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_child_task(char *cmd, char **args, t_info *info)
{
	char	**env;

	env = (char **)list_to_array(info->env);
	if (env == NULL)
		exit(EXIT_FAILURE);
	if (info->pipe_exists)
	{
		close(info->pipe[0]);
		if (dup2(info->pipe[1], STDOUT_FILENO) == -1)
			return (fd_log_error("Dup pipe error", NULL, NULL));
	}
	
	if (execve(cmd, args, env) == -1)
		exit(125 + execve_log_error(cmd, errno));
	// to do : add builtin
	//if (builtin)
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
	return (1);
}

int	dispatch_cmd(t_ast	*node, t_info *info)
{
	t_ast	*cmd_node;
	t_ast	*args_node;
	char	**args;
	int		status;

	cmd_node = node->left;
	args_node = node->right;
	printf("cmd_node data : %s\n", cmd_node->data);
	if (args_node)
		args = ft_split(args_node->data, ' ');
	else
		args = NULL;
	status = launch_process(cmd_node->data, args, info);
	info->pipe_exists = false;
	return (status);
}
