/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/08/23 16:42:05 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char **envp)
{
	char	*path;
	char	**res;

	path = ft_getenv("PATH", envp);
	if (!path)
		return (NULL);
	res = ft_split(path, ':');
	if (!res)
		return (NULL);
	return (res);
}

//act_p =actual pipe
void	ft_child_close_pipe(t_pipe *pipex)
{
	if (pipex->pipefd[pipex->act_p][0] && pipex->ctrl == -1)
	{
		if (pipex->pipefd[pipex->act_p][0] > -1)
			close(pipex->pipefd[pipex->act_p][0]);
		if (pipex->pipefd[pipex->act_p][1] > -1)
			close(pipex->pipefd[pipex->act_p][1]);
		pipex->ctrl = 0;
	}
}

//child built or cmd
void	b_o_c(char ***token, char ***envp, t_list *l_token, t_pipe *pipex)
{
	if (ft_builtins_fork(*token))
		ft_child_free2(token, envp, l_token, 0);
	if (!ft_builtins(*token, envp, pipex))
	{
		ft_pipex_exec(envp, l_token, *token, pipex);
		ft_child_free(token, envp, 127);
	}
	else
		ft_child_free2(token, envp, l_token, 0);
}

int	ft_child(char ***token, char ***envp, t_list *l_token, t_pipe *pipex)
{
	pid_t	child;

	if (ft_env_var(token, pipex->pipe_ret, l_token, *envp))
		return (FAILURE);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	child = fork();
	pipex->pid = child;
	if (child < 0)
		return (1);
	if (!child)
	{
		signal(SIGINT, ft_new_prompt);
		signal(SIGQUIT, SIG_DFL);
		fd_monitor(pipex);
		ft_close_tmp(pipex);
		b_o_c(token, envp, l_token, pipex);
	}
	parent2(token, envp, pipex);
	return (0);
}
