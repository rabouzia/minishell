/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:22:19 by junsan            #+#    #+#             */
/*   Updated: 2024/05/28 21:14:57 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free, exit
# include <unistd.h>   // write, access, close, fork, execve, pipe, dup, dup2
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <signal.h>   // signal, sigaction, sigemptyset, sigaddset, kill
# include <fcntl.h>    // open, read
# include <readline/readline.h> // readline
# include <readline/history.h> // add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <dirent.h>   // opendir, readdir, closedir
# include <sys/types.h> // stat, lstat, fstat, unlink
# include <sys/stat.h> // stat, lstat, fstat
# include <string.h>   // strerror
# include <errno.h>    // perror
# include <termios.h>  // isatty, ttyname, ttyslot, tcsetattr, tcgetattr
# include <sys/ioctl.h> // ioctl
# include <curses.h>   // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# define MAX_PATH_LENGTH 4096
# define HISTSIZE 500
# define DELIMS "|&<>"
# define ASCII_ART_PATH "assets/ascii_art_doh"

# define LEFT 0
# define RIGHT 1

typedef enum type
{
	SUBSHELL = 100,
	CMD = 20,
	IO = 6,
	REDIRECTION = 5,
	PIPE = 3,
	LOGICAL = 1,
	PHARSE = 0,
}	t_type;

typedef struct s_token
{
	int				num;
	char			*data;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
}	t_token_list;

typedef struct s_cmd
{
	char			*data;
	t_type			type;
	t_token			*token;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_cmd;

// tokenize_utils.c
t_token_list	*get_token_list(t_token *token);

void			add_token(t_token **head, const char *start, size_t len);

// init_minishell.c
void			init_minishell(void);
void			display_prompt(void);

// process_input.c
void			process_input(void);

// tokenize.c
void			tokenize(const char *input, t_token **tokens);

// tokenize_utlls_2.c
t_token			*tokens_last(t_token *tokens);
void			free_token(t_token *head);
size_t			tokens_size(t_token *head);

// string_utils.c
bool			ft_isspace(char c);

//  prints.c
void			print_token(t_token *head);
void			print_tree(t_cmd *root, int depth);

// parse_pratte.c
//t_cmd	*parse_expression(t_token **tokens, int min_bidning_power);
// parsing_utils.c
void			free_tree(t_cmd *node);
t_cmd			*new_node(t_token *token, t_type type);
t_cmd			*attach_to_tree(t_cmd *root, t_cmd *node, int side);
/*
// handler_parsing.c
void	handle_cmd_node(t_token *token, t_cmd **cur);
void	handle_logical_operator(\
		t_token **token, t_cmd **cur, t_cmd **root, bool *up_down_flag);
void	handle_pipe_operator(\
		t_token **token, t_cmd **cur, t_cmd **root, bool *up_down_flag);
void	handle_redirection_operator(\
		t_token **token, t_cmd **cur, t_cmd **root, bool *up_down_flag);
*/
// get_type.c
t_type			get_type(const char *data);

// type_functions.c
bool			islogical_operator(const char *token);
bool			ispipe_operator(const char *token);
bool			issubshell_operator(const char *token);
bool			isredirection_operator(const char *token);
bool			isioredirection_operator(const char *token);

// parsing.c
bool			parsing_tree(t_token_list **tokens, t_cmd **root);
void			free_tree(t_cmd *node);
t_cmd			*new_tree(t_token *token);

// get_type.c
bool			islogical_operator(const char *token);
bool			ispipe_operator(const char *token);
bool			issubshell_operator(const char *token);
bool			isredirection_operator(const char *token);
t_type			get_node_type(const char *data);
#endif // MINISHELL_H
