/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:25:11 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/19 09:57:31 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_free(char ***token, char ***envp, int ret)
{
	ft_split_free(*token);
	ft_split_free(*envp);
	exit(ret);
}

void	ft_child_free2(char ***token, char ***envp, t_list *l_token, int ret)
{
	ft_lstclear2(&l_token);
	ft_split_free(*token);
	ft_split_free(*envp);
	exit(ret);
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
	if (pipefd0 > 0)
		close(pipefd0);
	dup2(pipefd1, std);
	if (pipefd1 > -1)
		close(pipefd1);
	return (SUCCESS);
}
