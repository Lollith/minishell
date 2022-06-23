/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:07:23 by agouet            #+#    #+#             */
/*   Updated: 2022/06/23 12:02:47 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close_tmp(t_pipe pipex)
{
	if (close(pipex.tmp_in) < 0)
		return (msg_perror("tmp_in. "));
	if (close(pipex.tmp_out) < 0)
		return (msg_perror("tmp_out "));
	return (SUCCESS);
}

int	ft_link_fd(int pipefd0, int pipefd1, int std)
{
	if (close(pipefd0) < 0)
		return (msg_perror("pipefd0 "));
	if (dup2(pipefd1, std) == -1)
		return (msg_perror("dup2 "));
	if (close(pipefd1) < 0)
		return (msg_perror("pipefd1 "));
	return (SUCCESS);
}

int	ft_pipex(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	if (pipex.ctrl == 1)
		ft_link_fd(pipex.pipefd[1], pipex.pipefd[0], STDIN_FILENO);
	if (pipe(pipex.pipefd) < 0)
		return (msg_perror("pipe"));
	if (ft_child(args_exec, envp, l_token, pipex) <= 0)
		return (FAILURE);
	else
	{
		if (pipex.ctrl == 0)
			pipex.ctrl = 1;
		else
			pipex.ctrl = 0;
		monitoring_line(l_token->next->next, envp, pipex);
	}
	return (0);
}
