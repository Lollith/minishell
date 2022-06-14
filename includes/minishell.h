/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:29:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/02 15:19:24 by agouet           ###   ########.fr       */
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
/*                            debug.c 4 functions                             */
/* ************************************************************************** */
int		ft_msg(char *str, int fd);
int		msg_perror(char *origin);
int		ft_string_of_string_len(char **tab);
void	ft_print_string_of_string(char **tab);

/* ************************************************************************** */
/*                       environment_bis.c 0 functions                        */
/* ************************************************************************** */

/* ************************************************************************** */
/*                         environment.c 5 functions                          */
/* ************************************************************************** */
int		ft_strlen_equal(char *s);
char	**ft_unset_envp(char **line, char **envp);

/* ************************************************************************** */
/*                         builtins_bis.c 5 functions                         */
/* ************************************************************************** */
char	**ft_realloc_envp(char **envp);
int		ft_export(char **line, char **envp);
int		ft_unset(char **line, char ***envp);
int		ft_env(char **envp);

/* ************************************************************************** */
/*                           builtins.c 5 functions                           */
/* ************************************************************************** */
int		ft_exit(void);
int		ft_echo(char **line);
char	*get_home(char **envp);
int		ft_cd(char **line, char **envp);
int		ft_pwd(void);

/* ************************************************************************** */
/*                          ft_is_str.c 1 functions                           */
/* ************************************************************************** */
int		ft_is_str(char *line, char *str);

/* ************************************************************************** */
/*                       minishell_split.c 3 functions                        */
/* ************************************************************************** */
int		ft_is_space(char c, char *space);
int		minishell_quote(char const *str, int i);
int		minishell_len_quote(char const *str, int i, int *j);

/* ************************************************************************** */
/*                       minishell_split.c 5 functions                        */
/* ************************************************************************** */
char	**minishell_split(char const *s, char *space);

/* ************************************************************************** */
/*                          minishell.c 5 functions                           */
/* ************************************************************************** */
void	ft_free_split(char **str);
int		minishell(char *line, char **envp);
int		ft_builtins(char **line, char **envp);
char	**create_token_exec(char *cmd);

/* ************************************************************************** */
/*                           parsing.c 1 functions                            */
/* ************************************************************************** */
char	**lexer(char *line);

/* ************************************************************************** */
/*                            execut.c 4 functions                            */
/* ************************************************************************** */
char	**get_paths(char **envp);
void	ft_free_pa(char **paths, char *path_cmd, char **fake_token);
int		ft_child(char **paths, char *path_cmd, char **token, char **envp);
char	**ft_is_flag(t_list *l_token);
int		ft_exec(char **envp, char *cmd, char **new_token_exec);

/* ************************************************************************** */
/*                          list_token.c 2 functions                          */
/* ************************************************************************** */
int		list_token(t_list	**l_token, char *line);
void	ft_lstclear2(t_list **l_token);
void	ft_l_delete( t_list *delete);

/* ************************************************************************** */
/*                         ft_operator.c 3 functions                          */
/* ************************************************************************** */
int		monitoring_line(t_list *tmp_token, char **envp);
int		ft_eperluet( t_list *l_token, char **new_token_exec, char **envp);
int		ft_ou(t_list *tmp_token, char **new_token_exec, char **envp);
int		ft_redir_out(t_list *l_token, char **new_token_exec, char **envp);

/* ************************************************************************** */
/*                        minishell_pipe.c 3 functions                        */
/* ************************************************************************** */
int		ft_pipex(t_list *l_token, char **new_token_exec, char **envp);
int		ft_link_fd1(int *pipefd);
int		ft_link_fd2(int *pipefd);

/* ************************************************************************** */
/*                             main.c 4 functions                             */
/* ************************************************************************** */

#endif
