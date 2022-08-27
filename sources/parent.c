/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lollith <lollith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 14:51:35 by lollith           #+#    #+#             */
/*   Updated: 2022/08/27 14:57:03 by lollith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ret1(t_pipe *pipex)
{
	if (pipex->pipe_ret != 1)
		ft_pipe_ret(pipex);
	if (pipex->pipe_ret_b != -1)
		pipex->pipe_ret = pipex->pipe_ret_b;
}

int	parent(t_list *l_token, char ***envp, t_pipe *pipex)
{
	int	pid;
	int	wstatus;

	wstatus = 0;
	pipex->ctrl_redir_out = 0;
	pipex->tmp_in = dup(STDIN_FILENO);
	pipex->tmp_out = dup(STDOUT_FILENO);
	if (!next_checker(l_token))
		return (FAILURE);
	count_pipes(l_token, pipex);
	if (monitoring(l_token, l_token, envp, pipex) == 0)
		pipex->pipe_ret = 1;
	else
		pipex->pipe_ret = -1;
	ft_ret1(pipex);
	pid = wait(&wstatus);
	while (pid > 0)
		pid = wait(&wstatus);
	if (g_sig == 1)
		pipex->pipe_ret = 130;
	clean_std(pipex);
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, ft_new_prompt);
	return (SUCCESS);
}

void	ft_pipe_ret(t_pipe *pipex)
{
	int	wstatus;

	wstatus = 0;
	waitpid(pipex->pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		pipex->pipe_ret = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		pipex->pipe_ret = 128 + WTERMSIG(wstatus);
	else
		pipex->pipe_ret = 0;
}
