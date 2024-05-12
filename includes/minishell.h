/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junsan <junsan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 19:22:19 by junsan            #+#    #+#             */
/*   Updated: 2024/05/25 13:35:49 by junsan           ###   ########.fr       */
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

#ifndef ASCII_ART_PATH
# define ASCII_ART_PATH "assets/ascii_art_doh"
#endif

#ifndef MAX_PATH_LENGTH
# define MAX_PATH_LENGTH 1024
#endif

void init_minishell(void);

#endif // MINISHELL_H
