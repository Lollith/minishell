/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:29:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/25 10:11:13 by agouet           ###   ########.fr       */
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

# define FAILURE 0
# define SUCCESS 1
# define TRUE 1
# define FALSE 0

/* ************************************************************************** */
/*                             debug.c 0 functions                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                           ft_is_str.c 1 functions                          */
/* ************************************************************************** */
int		ft_is_str(char *line, char *str);

/* ************************************************************************** */
/*                        minishell_split.c 5 functions                       */
/* ************************************************************************** */
char	**minishell_split(char *str, char *space);

/* ************************************************************************** */
/*                           minishell.c 2 functions                          */
/* ************************************************************************** */
void	ft_free_split(char **str);
int		minishell(char *line, char **envp);

/* ************************************************************************** */
/*                            parsing.c 1 functions                           */
/* ************************************************************************** */
char	**lexer(char *line);

/* ************************************************************************** */
/*                            execut.c 4 functions                            */
/* ************************************************************************** */
char	**get_paths(char **envp);
void	ft_exec(char **envp, char **token);

/* ************************************************************************** */
/*                             main.c 4 functions                             */
/* ************************************************************************** */
int		ft_msg(char *str, int fd);
void	ft_new_prompt(int signum);
int		check_env(char **envp);

#endif
