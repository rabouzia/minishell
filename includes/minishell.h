/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:22:19 by junsan            #+#    #+#             */
/*   Updated: 2024/06/24 15:26:00 by junsan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <dirent.h> // opendir, readdir, closedir
# include <errno.h>  // perror
# include <fcntl.h>  // open, read
# include <limits.h>
# include <readline/history.h>
// add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/readline.h> // readline
# include <signal.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <stdbool.h>
# include <stdio.h>     // printf
# include <stdlib.h>    // malloc, free, exit
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/types.h> // stat, lstat, fstat, unlink
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <termios.h>   // isatty, ttyname, ttyslot, tcsetattr, tcgetattr
# include <unistd.h>    // write, access, close, fork, execve, pipe, dup, dup2

# define MAX_PATH_LENGTH 4096
# define MEMORY_CAPACITY 256
# define HISTSIZE 500
# define DELIMS "|&<>"
# define ARR_SEP '|'
# define ASCII_ART_PATH "assets/ascii_art_doh"
# define HEREDOC_TMP "heredoc_tmp"

typedef enum tree_direction
{
	LEFT,
	RIGHT,
}	t_tree_direction;

typedef enum type_dir
{
	IS_DIRECTORY = 126,
	CMD_NOT_FOUND = 127,
}	t_type_dir;

typedef enum type_descriptor
{
	READ,
	WRITE,
	APPEND,
}	t_type_descriptor;

typedef enum status
{
	SUCCESS,
	FAILURE,
	MALLOC_ERR,
}	t_status;

typedef enum type_logical
{
	AND,
	OR,
}						t_type_logical;

typedef enum type
{
	SUBSHELL = 100,
	ARGS = 22,
	CMD = 20,
	FILE_NAME = 18,
	IO = 6,
	REDIRECTION = 5,
	PIPE = 3,
	LOGICAL = 1,
	PHRASE = 0,
	IN_REDIR = 7,
	IN_HEREDOC = 8,
	IN_HERESTR = 9,
	OUT_REDIR = 10,
	OUT_APPEND = 11,
	NOT_REDIR = 12,
}						t_type;

typedef enum error
{
	UNCLOSED_QUOTE,
	TOKEN_ERROR,
	PARSE_ERROR,
}	t_error;

typedef enum path_type
{
	PATH_ABSOLUTE,
	PATH_RELATIVE,
	PATH_COMMAND,
	PATH_INVALID
}	t_path_type;

typedef enum built_in
{
	M_ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NONE,
}						t_built_in;

typedef struct s_env
{
	char				*name;
	char				*content;
	struct s_env		*pwd;
	struct s_env		*old_pwd;
	struct s_env		*next;
}						t_env;

typedef struct s_info
{
	bool				pipe_exists; // pipe exist or not
	bool				pipe_used;	// used pipe befor
	bool				in_subshell;
	char				*path;
	int					stdin_fd;
	int					stdout_fd;
	int					origin_stdin_fd;
	int					origin_stdout_fd;
	int					pipe[2];
	int					tmp_fd;
	int					exit_status;
	int					status; // can proceed by logical
	t_env				*env;
}						t_info;

typedef struct s_token
{
	int					num;
	char				*data;
	t_type				type;
	struct s_token		*next;
}						t_token;

typedef struct s_token_list
{
	t_token				*head;
	t_token				*tail;
}						t_token_list;

typedef struct s_ast
{
	char				*data;
	t_type				type;
	t_token				*token;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef struct s_cmd_list
{
	char				*cmd;
	struct s_cmd_list	*prev;
	struct s_cmd_list	*next;
}						t_cmd_list;

typedef struct s_file_list
{
	char				**names;
	size_t				count;
}						t_file_list;

// process_input.c
void					process_input(\
		char *input, t_env *env, int *exit_status);

// --------------------------- init --------------------------//
// init_minishell.c
void					init_minishell(char **envp, t_env **env);

// env_init.c
void					add_env(t_env **head, const char *str);
t_env					*env_init(char **envp);

// env_utils.c
size_t					env_size(t_env *head);
void					clear_env(t_env *head);

// increment_shlvl.c
int						increment_shlvl(t_env *env);

// ------------------------ parsing ---------------------------//
// parsing_utils.c
void					free_tree(t_ast *node);
t_ast					*new_node(const char *data, t_type type);
t_ast					*attach_to_tree(t_ast *root, t_ast *node, int side);
void					remove_outer_parentheses(char **str, t_ast **root);
// parsing.c
bool					parsing_tree(t_token_list **tokens, t_ast **root);

// parse_logical.c
bool					parse_logical(t_token **token, t_ast **node);

// parse_pipe.c
bool					parse_pipe(t_token **token, t_ast **node);

// parse_phrase.c
bool					parse_phrase(t_token **token, t_ast **node);

// parse_redirection.c
bool					parse_redirection(t_token **token, t_ast **node);
bool					parse_io_redirection(t_token **token, t_ast **node);

// parse_subshell.c
bool					parse_subshell(t_token **token, t_ast **node);

// type_functions.c
bool					is_logical_operator(const char *token);
bool					is_pipe_operator(const char *token);
bool					is_subshell_operator(const char *token);
bool					is_redirection_operator(const char *token);
bool					is_file_name(const char *token);

// subshell_utils.c
char					*remove_nested_subshell(t_token **token);

// type_redir_functions.c
bool					is_input_redirection(const char *data);
bool					is_output_redirection(const char *data);
bool					is_append_redirection(const char *data);
bool					is_heredoc_redirection(const char *data);
bool					is_herestr_redirection(const char *data);

// arg_parse.c
bool					is_flag(const char *arg);
char					*arg_parsing(t_token **token);

// get_type.c
t_type					get_type(const char *data);
t_type					get_type_redir(const char *data);

// ------------------------ tokenize --------------------------//
// tokenize.c
void					tokenize(const char *input, t_token **tokens);

// tokenize_utils.c
t_token_list			*get_token_list(t_token *token);
void					add_token(\
		t_token **head, const char *start, size_t len);

// handle_quotes.c
void					handle_quotes(const char **input, char *in_quote,
							const char **start, t_token **list);

// handle_subshell.c
void					handle_open_subshell(const char **input, int *depth,
							const char **start, t_token **list);
void					handle_close_subshell(const char **input, int *depth,
							const char **start, t_token **list);

// handle_operators_and_spaces.c
void					handle_operators_and_spaces(const char **input,
							const char **start, t_token **list);
// tokenize_utlls_2.c
t_token					*tokens_last(t_token *tokens);
void					free_token(t_token *head);
size_t					tokens_size(t_token *head);

// valid_token.c
int						valid_token(t_token *head);

// ------------------------ signal ---------------------------//
// handler_signal.c
void					set_signal_handler(void);
void					disable_interrupt_signals(void);

// ------------------------ execute --------------------------//
// execute.c
void					execute(t_ast *root, t_env *env, int *exit_status);

// execute_process.c
void					process_cmd_node(t_ast *node, t_info *info);
void					process_io_redirection_node(t_ast *node, t_info *info);
void					process_phrase_node(t_ast *node, t_info *info);

// info_utils.c
void					init_info(t_info *info);
void					clear_info(t_info *info);
// args_utils.c
void					free_args(char **args);
void					replace_env_vars_in_args(char **args, t_info *info);
void					remove_quotes_from_args(char **args);
char					**allocate_null_and_cmd_chunk(const char *cmd);

// var_expansion_with_args.c
void					replace_env_vars_in_args(char **args, t_info *info);

// get_path_type.c
t_path_type				get_path_type(const char *path, t_info *info);

// find_cmd_in_path.c
char					*find_cmd_in_path(const char *cmd, t_env *env);

// get_absolute_path.c
char					*get_absolute_path(const char *path);

// stdio_redirector.c
int						backup_stdio(t_info *info);
int						restore_stdio(t_info *info);

// get_file_list.c
void					free_file_list(t_file_list *file_list);
const char				*get_path(const char *full_path);
t_file_list				*get_file_list(const char *path);

// get_file_list_utils.c
DIR						*get_dir(const char *path, int file_count,
							t_file_list **file_list);
t_file_list				*get_entry_list(t_file_list *file_list, DIR *dir);

// list_to_array.c
char					**list_to_array(t_env *env);
void					clear_arr(int len, char **arr);

// cmd.c
int						dispatch_cmd(t_ast *node, t_info *info);

// launch_process.c
int						launch_process(char *cmd, char **args, t_info *info);

// redir.c
int						handle_io_redirection(t_ast *node, t_info *info);

// redir_utils.c
int						here_doc(int infile, char *limiter);
int						open_file_with_mode(char *file, int mode);
void					cleanup_tmp_file(void);

// ------------------------ utils -----------------------------//
// string_utils.c
bool					ft_isspace(char c);
bool					is_all_whitespace(const char *str);
void					remove_control_characters(char *str);
int						count_repeated_chars(const char *str, int c);

// string_utils_2.c
char					*trim_first_last(char *str);
char					*trim_whitespace(const char *str);
char					*ft_strndup(const char *str, size_t n);
void					remove_quotes(char *str);

// error_utils.c
int						fd_log_error(char *cmd, char *arg, char *error);
int						execve_log_error(char *cmd, int error);
void					parse_log_error(int err, int *exit_status);

// --------------------------- built_in --------------------------//

// built_in.c
void					init_builtin(int (*func[])(const char *, const char **,
								t_env *));
int						handler_builtin(const char *cmd);

// file_dir_operations.c
int						change_dir(const char *path, t_env *lst);
bool					get_cur_dir(void);
bool					file_exist(const char *filename);
void					list_dir(const char *dirname);

// ft_cd.c
void					ist_swap(t_env *a);
int						ft_cd(const char *cmd, const char **args, t_env *list);

// ft_echo.c
int						ft_echo(const char *cmd, const char **args,
							t_env *list);

// ft_env.c
void					add_builtin_node(t_env **head, char *name,
							char *content);
void					printf_env(t_env *list);
int						ft_env(const char *cmd, const char **args, t_env *list);
char					*ft_strndup(const char *src, size_t n);
t_env					*builtin_new_node(char *name, char *content);
t_env					*fill_env(int ac, char **av, char **env);

// ft_exit.c
int						ft_exit(const char *cmd, const char **args,
							t_env *list);

// ft_export.c
// void			ft_export_add(char *var, char **arg);
// void			ft_export_show(t_env *env);
// int				ft_export(char *cmd, char **args, t_env *list);
// t_env			*sort_list(t_env *env);

// ft_pwd.c
int						ft_pwd(const char *cmd, const char **args, t_env *list);

// ft_unset.c
int						ft_unset(const char *cmd, const char **args,
							t_env *list);

// subshell_utils.c
char					*remove_nested_subshell(t_token **token);

// --------------------------- print --------------------------//
//  prints.c
void					print_token(t_token *head);
void					print_file_list(t_file_list *file_list);

//	prints_2.c
void					print_tree(t_ast *root, int depth);

#endif // MINISHELL_H
