/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:29:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/30 10:06:14 by agouet           ###   ########.fr       */
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

/*---------------------------------------------------------------------------*/
//							 minishell.c	2 functions
/*---------------------------------------------------------------------------*/
void	minishell(char *line, char **envp);
void	ft_free_split(char **str);

/*---------------------------------------------------------------------------*/
//								parsing.c
/*---------------------------------------------------------------------------*/
char	**lexer(char *line);

/*---------------------------------------------------------------------------*/
//								execut.c
/*---------------------------------------------------------------------------*/
char	**get_paths(char **envp);
void	ft_free_pa(char **paths, char *path_cmd, char **fake_token); // attention modif , com a sup
int		ft_child(char **path, char *path_cmd, char **n_tokn_ex, char **env); // prise sur la branche de fr, com a sup
char	**create_token_exec(char *cmd);
int		ft_exec(char **envp, char *cmd, char **new_token_exec); // attention modif, com a sup

/*---------------------------------------------------------------------------*/
//								list_token.c
/*---------------------------------------------------------------------------*/
int		list_token(t_list	**l_token, char *line);
void	ft_lstclear2(t_list **l_token);

/*---------------------------------------------------------------------------*/
//								ft_operator.c
/*---------------------------------------------------------------------------*/
void	monitoring_line(t_list *tmp_token, char **envp);
int		ft_eperluet( t_list *l_token, char **envp);
int		ft_ou(t_list *tmp_token, char **envp);

/*---------------------------------------------------------------------------*/
//								 main.c	    3 functions
/*---------------------------------------------------------------------------*/
int		ft_msg(char *str, int fd);
void	ft_new_prompt(int signum);
int		check_env(char **envp);

#endif