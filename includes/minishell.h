/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:22:19 by junsan            #+#    #+#             */
/*   Updated: 2024/05/26 16:11:22 by junsan           ###   ########.fr       */
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

# ifndef ASCII_ART_PATH
#  define ASCII_ART_PATH "assets/ascii_art_doh"
# endif

# ifndef MAX_PATH_LENGTH
#  define MAX_PATH_LENGTH 4096
# endif

# ifndef HISTSIZE
#  define HISTSIZE 500
# endif

# ifndef DELIMS
#  define DELIMS "|&<>"
# endif

typedef enum type
{
	CMD,
	REDIRECTION,
	PIPE,
	LOGICAL
}	t_type;

typedef struct s_token
{
	char			*data;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*data;
	t_type			type;
	struct s_cmd	*left;
	struct s_cmd	*right;
}	t_cmd;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
}	t_token_list;

// init_minishell.c
void	init_minishell(void);
void	display_prompt(void);

// process_input.c
void	process_input(void);

// tokenize.c
void	tokenize(const char *input, t_token **tokens);

// tokenize_utils.c
t_token	*tokens_last(t_token *tokens);
void	add_token(t_token **head, const char *start, size_t len);
void	free_token(t_token **head);
size_t	tokens_size(t_token *head);

// string_utils.c
bool	ft_isspace(char c);

//  prints.c
void	print_token(t_token *head);
void	print_tree(t_cmd *root, int depth);

// parsing.c
t_cmd	*parsing_tree(t_token **tokens, t_token_list **token_list);

// parsing_utils.c
void	free_tree(t_cmd *node);
bool	islogical_operator(const char *token);
bool	ispipe_operator(const char *token);
bool	isredirection_operator(const char *tonen);
t_cmd	*new_tree(const char *data, t_type type);
#endif // MINISHELL_H
