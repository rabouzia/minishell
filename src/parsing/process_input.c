/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabouzia <rabouzia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:45:45 by junsan            #+#    #+#             */
/*   Updated: 2024/06/02 02:36:23 by rabouzia         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(char **command)
{
	if (execvp(command[0], command) == -1)
	{
		perror("execvp");
	}
	exit(EXIT_FAILURE);
}

void	execute_ast(t_ast *node)
{
	char	*cmd[] = {node->data, NULL};
	int		pipefd[2];

	if (node == NULL)
		return ;
	if (node->left == NULL && node->right == NULL)
	{
		// It's a simple command, no pipe
		if (fork() == 0)
		{
			execute_command(cmd);
		}
		else
		{
			wait(NULL);
		}
	}
	else if (node->right != NULL)
	{
		pipe(pipefd);
		if (fork() == 0)
		{
			// Child process: execute left command and write to pipe
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			execute_command(cmd);
		}
		else
		{
			// Parent process: execute right command and read from pipe
			if (fork() == 0)
			{
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
				execute_ast(node->right);
			}
			else
			{
				close(pipefd[0]);
				close(pipefd[1]);
				wait(NULL);
				wait(NULL);
			}
		}
	}
}

void	process_input(char *input, main_arg *arg)
{
	t_token_list	*token_list;
	t_token			*tokens;
	t_ast			*root;

	tokens = NULL;
	root = NULL;
	if (input)
	{
		if (ft_strncmp(input, "env", 3) == 0)
			print_env(arg);
		tokenize(input, &tokens);
		token_list = get_token_list(tokens);
		print_token(tokens);
		(void)root;
		parsing_tree(&token_list, &root);
		print_tree(root, 10);
		// execute_ast(root);
		free_tree(root);
		free(token_list);
		free_token(tokens);
		free(input);
	}
}
