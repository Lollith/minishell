/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:29:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/19 14:29:42 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>// write access read close dup dup2 execve fork pipe unlink
# include <fcntl.h>// open
# include <stdlib.h>// malloc free getenv
# include <stdio.h>// printf exit perror
# include <string.h>// strerror
# include <dirent.h>// opendir readdir closedir
# include <signal.h>// signal sigaction sigemptyset sigaddset kill
# include <termios.h>// tcsetattr tcgetattr tgetent tgetflag tgetnum tgetstr
# include <sys/wait.h>// wait waitpid wait3 wait4
# include <sys/stat.h>// stat lstat fstat
# include <sys/ioctl.h>// ioctl
# include <readline/readline.h>// rl_on_new_line rl_replace_line rl_redisplay
# include <readline/history.h>// rl_clear_history add_history
// <readline/readline.h> readline
// <unistd.h> getcwd chdir isatty ttyname ttyslot
// <termios.h> tgoto tputs

// minishell.c	1 functions
void	minishell(char *line, char **env);

// main.c	    4 functions

#endif
