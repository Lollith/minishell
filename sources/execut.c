/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/08/08 17:36:26 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(void)
{
	char	*path;
	char	**res;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	res = ft_split(path, ':');
	if (!res)
		return (NULL);
	return (res);
}

void	ft_child_close_pipe(t_pipe *pipex)
{
	if (pipex->pipefd[0] && pipex->ctrl == -1)
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		pipex->ctrl = 0;
	}
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
		fd_monitor(pipex);
		ft_close_tmp(pipex);
		if (ft_builtins_fork(*token))
			ft_child_free2(token, envp, l_token, 0);
		ft_pipex_exec(envp, l_token->content, *token, pipex);
		ft_child_free(token, envp, l_token, 127);
	}
	if (ft_builtins(*token, envp, l_token, pipex) == 2)
		ft_child_free(token, envp, l_token, 1);
	ft_child_close_pipe(pipex);
	return (0);
}

void	fd_monitor(t_pipe *pipex)
{
	if ((pipex->ctrl == 0 || pipex->ctrl == 1) && pipex->pipefd[0])
		ft_link_fd(pipex->pipefd[0], pipex->pipefd[1], STDOUT_FILENO);
	if (pipex->pipefd[0] && pipex->ctrl == -1)
		ft_link_fd(pipex->pipefd[1], pipex->pipefd[0], STDIN_FILENO);
}

int	ft_link_fd(int pipefd0, int pipefd1, int std)
{
	if (pipefd0)
		close(pipefd0);
	dup2(pipefd1, std);
	close(pipefd1);
	return (SUCCESS);
}
