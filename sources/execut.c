/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/07/13 17:30:35 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pa(char **paths, char *path_cmd, char **token)
{
	if (paths)
		ft_split_free(paths);
	if (path_cmd)
		free(path_cmd);
	if (token)
		ft_split_free(token);
}

char	**get_paths(void)
{
	char	*path;
	char	**res;

	path = getenv("PATH");
	res = ft_split(path, ':');
	if (!res)
		return (NULL);
	return (res);
}

int	ft_child(char **args_exec, char ***envp, t_list *l_token, t_pipe *pipex)
{
	pid_t	child;

	child = fork();
	pipex->pid = child;
	if (child < 0)
		return (1);
	if (!child)
	{
		if ((pipex->ctrl == 0 || pipex->ctrl == 1) && pipex->pipefd[0])
			ft_link_fd(pipex->pipefd[0], pipex->pipefd[1], STDOUT_FILENO);
		if (pipex->pipefd[0] && pipex->ctrl == -1)
			ft_link_fd(pipex->pipefd[1], pipex->pipefd[0], STDIN_FILENO);
		if (ft_pipex_exec(*envp, l_token->content, args_exec, pipex) == 0)
			exit (127);
		return (1);
	}
	if (pipex->pipefd[0] && pipex->ctrl == -1)
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		pipex->ctrl = 0;
	}
	return (0);
}
