/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:57:26 by agouet            #+#    #+#             */
/*   Updated: 2022/06/17 16:08:33 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(int ac, char **av, char **envp, t_pipe *pipex)
{
	pipex->ctrl = 0;
	pipex->pipefd[0] = 0;
	if (ft_main(ac, av, &envp))
		return (FAILURE);
	return (SUCCESS);
}

int	fd_monitor(t_list *tmp_token, char **envp, t_pipe pipex)
{
	int	tmp_in;
	int	tmp_out;
	int	pid;
	int	wstatus;

	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	monitoring_line(tmp_token, envp, pipex);
	pid = wait(&wstatus);
	while (pid > 0)
		pid = wait(&wstatus);
	if (dup2(tmp_in, STDIN_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (dup2(tmp_out, STDOUT_FILENO) == -1)
		return (msg_perror("dup2 "));
	return (SUCCESS);
}
