/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:29:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/07/13 15:05:44 by agouet           ###   ########.fr       */
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
# define BUFFER_NAME 128

typedef struct s_pipe
{
	int	ctrl;
	int	pipefd[2];
	int	tmp_in;
	int	tmp_out;
}				t_pipe;

/* ************************************************************************** */
/*   debug.c                                                    5 functions   */
/* ************************************************************************** */
int		ft_free_args_exec(char **args_exec, int ret);
int		ft_msg(char *str, int fd);
int		msg_perror(char *origin);
int		ft_string_of_string_len(char **tab);
void	ft_print_string_of_string(char **tab);

/* ************************************************************************** */
/*   environment_bis.c                                          2 functions   */
/* ************************************************************************** */
int		ft_export_value(char **line, char ***envp, int i);
char	**ft_export_envp(char **line, char **envp);

/* ************************************************************************** */
/*   environment.c                                              5 functions   */
/* ************************************************************************** */
int		ft_unset_str(char **line, char **envp, int i, int *k);
int		ft_strlen_equal(char *s);
char	*ft_str_whitout_equal(char *envp);
char	**ft_unset_free(int i, char **res);
char	**ft_unset_envp(char **line, char **envp);

/* ************************************************************************** */
/*   builtins_bis.c                                             5 functions   */
/* ************************************************************************** */
char	**ft_realloc_envp(char **envp);
int		ft_export(char **line, char ***envp);
int		ft_unset(char **line, char ***envp);
int		ft_env(char **envp);

/* ************************************************************************** */
/*   builtins.c                                                 5 functions   */
/* ************************************************************************** */
int		ft_exit(void);
int		ft_echo(char **line);
char	*get_home(char **envp);
int		ft_cd(char **line, char **envp);
int		ft_pwd(void);

/* ************************************************************************** */
/*   ft_is_str.c                                                1 functions   */
/* ************************************************************************** */
int		ft_is_str(char *line, char *str);

/* ************************************************************************** */
/*   minishell_split_utils.c                                    0 functions   */
/* ************************************************************************** */

/* ************************************************************************** */
/*   minishell_split_bis.c                                      4 functions   */
/* ************************************************************************** */
int		ft_is_space(char c, char *space);
int		minishell_quote(char const *str, int i);
int		minishell_len_quote_bis(char const *str, int i, int *j, char c);
int		minishell_len_quote(char const *str, int i, int *j);

/* ************************************************************************** */
/*   minishell_split.c                                          5 functions   */
/* ************************************************************************** */
char	**minishell_split(char const *s, char *space);

/* ************************************************************************** */
/*   minishell.c                                                3 functions   */
/* ************************************************************************** */
int		minishell(char *line, char ***envp);
int		ft_builtins(char **line, char ***envp);
char	**create_token_exec(char *cmd);

/* ************************************************************************** */
/*   parsing.c                                                  4 functions   */
/* ************************************************************************** */
char	**lexer(char *line);
int		size_args(t_list *l_token);
char	**ft_is_arg(t_list *l_token);

/* ************************************************************************** */
/*   parsing2.c                                                 2 functions   */
/* ************************************************************************** */
int		is_operator(t_list *l_token);
int		is_cmd(t_list *l_token);

/* ************************************************************************** */
/*   execut.c                                                   5 functions   */
/* ************************************************************************** */
char	**get_paths(void);
void	ft_free_pa(char **paths, char *path_cmd, char **fake_token);
int		ft_exec(char **envp, char *cmd, char **args_exec);
int		ft_child(char **args_exe, char ***envp, t_list *l_token, t_pipe pipex);
int		ft_old_child(char **paths, char *path_cmd, char **token, char **envp);

/* ************************************************************************** */
/*  list_token.c                                                3 functions   */
/* ************************************************************************** */
int		list_token(t_list	**l_token, char *line);
void	ft_lstclear2(t_list **l_token);
void	ft_l_delete(t_list *delete);

/* ************************************************************************** */
/*   operator_bonus.c                                           2 functions   */
/* ************************************************************************** */
int		ft_eperluet(t_list *l_tok, char **arg_exec, char ***envp, t_pipe pipex);
int		ft_ou(t_list *tmp_token, char **arg_exec, char ***envp, t_pipe pipex);

/* ************************************************************************** */
/*   operator.c                                                 5 functions   */
/* ************************************************************************** */
int		ft_redir_out(t_list *l_tok, char **arg_exe, char ***envp, t_pipe pipex);
int		open_out(t_list *l_token, char **args_exec);
int		ft_redir_in(t_list *l_tok, char **arg_exe, char ***envp, t_pipe pipex);
char	*open_in(t_list *l_token, char **args_exec);

/* ************************************************************************** */
/*   heredoc.c                                                 5 functions   */
/* ************************************************************************** */
char	*creat_h_file(void);
char	*check_here_file(void);
char	*ft_heredoc(t_list *l_token);
void	free_heredoc(char *file1);
char	*init_hd(int *pt_fd);

/* ************************************************************************** */
/*   operator.c                                           2 functions   */
/* ************************************************************************** */
int		monitoring_line(t_list *tmp_token, char ***envp, t_pipe pipex);
void	reorganize(t_list **l_token);

/* ************************************************************************** */
/*   minishell_pipe.c                                           2 functions   */
/* ************************************************************************** */
int		ft_pipex(t_list *l_token, char **args_exec, char ***envp, t_pipe pipe);
int		ft_link_fd(int pipefd0, int pipefd1, int std);
int		ft_close_tmp(t_pipe pipex);
int		ft_pipex_exec(char **envp, char *cmd, char **args_exec, t_pipe fds);
char	*get_paths_cmd(char *paths_i, char *cmd);

/* ************************************************************************** */
/*   initialisation.c                                           5 functions   */
/* ************************************************************************** */
int		init(int ac, char **av, char ***envp, t_pipe *pipex);
int		fd_monitor(t_list *tmp_token, char ***envp, t_pipe pipex);

/* ************************************************************************** */
/*   main.c                                                     2 functions   */
/* ************************************************************************** */

#endif
