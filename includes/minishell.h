/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 14:29:36 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/03 15:36:28 by agouet           ###   ########.fr       */
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

extern int	g_sig;

# define FAILURE 0
# define SUCCESS 1
# define TRUE 1
# define FALSE 0
# define BUFFER_NAME 32
# define MS_SPACE " \t\n\v\f\r"

typedef struct s_pipe
{
	int		pipe_ret;
	int		ctrl;
	int		pipefd[2];
	int		tmp_in;
	int		tmp_out;
	pid_t	pid;
}			t_pipe;

/* ************************************************************************** */
/*   builtins/builtins_bis.c                                    5 functions   */
/* ************************************************************************** */
char	**ft_realloc_envp(char **envp);
int		ft_env_parsing(char **line, int is_unset);
int		ft_export(char **line, char ***envp);
int		ft_unset(char **line, char ***envp);
int		ft_env(char **envp);

/* ************************************************************************** */
/*   builtins/builtins.c                                        5 functions   */
/* ************************************************************************** */
int		ft_exit(char **line, char **envp);
int		ft_echo(char **line);
char	*ft_get_home(char **envp);
int		ft_cd(char **line, char ***envp);
int		ft_pwd(char **envp);

/* ************************************************************************** */
/*   builtins/environment_bis.c                                 4 functions   */
/* ************************************************************************** */
int		ft_export_value(char **line, char ***envp, int i);
char	**ft_export_envp(char **line, char **envp);
char	**ft_export_line(char *pwd);
int		ft_echo_cheak(char *line);

/* ************************************************************************** */
/*   builtins/environment.c                                     5 functions   */
/* ************************************************************************** */
int		ft_strlen_equal(char *s);
char	*ft_str_whitout_equal(char *envp);
int		ft_unset_str(char **line, char **envp, int i, int *k);
char	**ft_unset_free(int i, char **res);
char	**ft_unset_envp(char **line, char **envp);

/* ************************************************************************** */
/*   minishell_split/ft_env_pipe.c                              2 functions   */
/* ************************************************************************** */
int		ft_env_pipe_size(int pipe_ret, int *i);
void	ft_env_pipe_input(char *res, int pipe_ret, int *i, int *j);
void	ft_env_free(void **tmp1, void **tmp2, t_list *l_token);

/* ************************************************************************** */
/*   minishell_split/ft_env.c                                   5 functions   */
/* ************************************************************************** */
int		ft_env_var(char ***token, int pipe_ret, t_list *l_token, char **envp);

/* ************************************************************************** */
/*   minishell_split/minishell_split_bis.c                      4 functions   */
/* ************************************************************************** */
int		ft_is_space(char c, char *space);
int		minishell_quote(char const *str, int i);
int		minishell_len_quote_bis(char const *str, int i, int *j, char c);
int		minishell_len_quote(char const *str, int i, int *j);

/* ************************************************************************** */
/*   minishell_split/minishell_split.c                          5 functions   */
/* ************************************************************************** */
char	**minishell_split(char const *s, char *space);

/* ************************************************************************** */
/*   operator/heredoc.c                                         5 functions   */
/* ************************************************************************** */
char	*creat_h_file(void);
char	*check_here_file(void);
char	*ft_heredoc(char **args_exec);
void	free_heredoc(char *file1);
char	*init_hd(int *pt_fd);

/* ************************************************************************** */
/*   operator/minishell_pipe.c                                  5 functions   */
/* ************************************************************************** */
int		ft_close_tmp(t_pipe *pipex);
int		ft_pipex(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipe);
int		ft_pipex_exec(char ***envp, char *cmd, char **args_exec, t_pipe *fds);
char	*get_paths_cmd(char *paths_i, char *cmd);
int		ft_pipex_exec_return(char **paths, char *cmd);

/* ************************************************************************** */
/*   operator/operator_bonus.c                                  2 functions   */
/* ************************************************************************** */
int		ft_eperluet(t_list *l_tok, char **arg_exec, char ***envp, t_pipe *pip);
int		ft_ou(t_list *tmp_token, char **arg_exec, char ***envp, t_pipe *pipex);

/* ************************************************************************** */
/*   operator/operator.c                                        5 functions   */
/* ************************************************************************** */
int		ft_redir_out(t_list *l_tok, char **arg_exe, char ***envp, t_pipe *pip);
int		open_out(t_list *l_token, char **args_exec);
int		ft_redir_in(t_list *l_tok, char **arg_exe, char ***envp, t_pipe *pipex);
char	*open_in(t_list *l_token, char **args_exec);
int		next_checker(t_list *l_token);

/* ************************************************************************** */
/*   parsing/ft_quoting.c                                       5 functions   */
/* ************************************************************************** */
int		ft_quoting_quote(char const *str, int *i, char c);
int		ft_quoting_quoting(char const *str, int *i);
int		ft_d_quote(char const *str, char *res, int *i, int size);
int		ft_s_quote(char const *str, char *res, int *i, int size);
void	ft_quoting_res(char const *str, char *res, int *i, int *size);

/* ************************************************************************** */
/*   parsing/list_token.c                                       3 functions   */
/* ************************************************************************** */
int		list_token(t_list **l_token, char *line);
void	ft_l_delete(t_list *l_token);
void	ft_lstclear2(t_list **l_token);

/* ************************************************************************** */
/*   parsing/parsing.c                                          4 functions   */
/* ************************************************************************** */
int		ft_quote(char *line);
char	**lexer(char *line);
int		size_args(t_list *l_token);
char	**ft_is_arg(t_list *l_token);

/* ************************************************************************** */
/*   parsing/parsing2.c                                         1 functions   */
/* ************************************************************************** */
char	*ft_first_strchr(const char *s, int c);
int		is_operator(t_list *l_token);
int		is_cmd(t_list *l_token);

/* ************************************************************************** */
/*   useful/ft_getenv.c                                        1 functions   */
/* ************************************************************************** */
char	*ft_getenv(char *env, char **envp);

/* ************************************************************************** */
/*   useful/ft_is_int.c                                         3 functions   */
/* ************************************************************************** */
int		ft_is_int(char *line);

/* ************************************************************************** */
/*   useful/ft_is_str.c                                         1 functions   */
/* ************************************************************************** */
int		ft_is_str(char *line, char *str);

/* ************************************************************************** */
/*   useful/useful.c                                            5 functions   */
/* ************************************************************************** */
int		ft_free_args_exec(char **args_exec, int ret);
int		ft_msg(char *str, int fd);
int		msg_perror(char *origin);
int		ft_string_of_string_len(char **tab);
void	ft_print_string_of_string(char **tab);

/* ************************************************************************** */
/*   execut_bis.c                                               1 functions   */
/* ************************************************************************** */
void	ft_child_free(char ***token, char ***envp, t_list *l_token, int ret);

/* ************************************************************************** */
/*   execut.c                                                   5 functions   */
/* ************************************************************************** */
char	**get_paths(void);
void	ft_child_close_pipe(t_pipe *pipex);
int		ft_child(char ***token, char ***envp, t_list *l_token, t_pipe *pipex);
void	fd_monitor(t_pipe *pipex);
int		ft_link_fd(int pipefd0, int pipefd1, int std);

/* ************************************************************************** */
/*   minishell.c                                                4 functions   */
/* ************************************************************************** */
int		ft_builtins_fork(char **line);
int		ft_builtins(char **line, char ***envp);
void	ft_quoting_input(char const *str, char *res);
char	*ft_quoting(char const *str);

/* ************************************************************************** */
/*   monitor.c                                                  5 functions   */
/* ************************************************************************** */
int		reorganize(t_list **l_token, char **args_exec, char ***file_redir);
void	reorga2(t_list **l_token, t_list *tmp);
int		monitoring_line(t_list *tmp_token, char ***envp, t_pipe *pipex);
int		one_cmd(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex);

/* ************************************************************************** */
/*   initialisation.c                                           4 functions   */
/* ************************************************************************** */
void	ft_new_prompt(int signum);
void	signal_here_doc(int signum);
int		check_env(char **envp);
int		ft_main(int ac, char **av, char ***envp);
int		init(int ac, char **av, char ***envp, t_pipe *pipex);

/* ************************************************************************** */
/*   main.c                                                     4 functions   */
/* ************************************************************************** */
int		parent(t_list *tmp_token, char ***envp, t_pipe *pipex);
void	ft_pipe_ret(t_pipe *pipex);
void	ft_new_prompt(int signum);

#endif
