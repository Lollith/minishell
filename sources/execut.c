/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/07/08 14:51:27 by agouet           ###   ########.fr       */
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

void	ft_child_close_pipe(t_pipe pipex)
{
	if (pipex.pipefd[0] && pipex.ctrl == -1)
	{
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
		pipex.ctrl = 0;
	}
}

int	ft_child(char ***token, char ***envp, t_list *l_token, t_pipe pipex)
{
	pid_t	child;

	if (ft_env_var(token))
		return (FAILURE);
	child = fork();
	if (child < 0)
		return (FAILURE);
	if (!child)
	{
		if ((pipex.ctrl == 0 || pipex.ctrl == 1) && pipex.pipefd[0])
			ft_link_fd(pipex.pipefd[0], pipex.pipefd[1], STDOUT_FILENO);
		if (pipex.pipefd[0] && pipex.ctrl == -1)
			ft_link_fd(pipex.pipefd[1], pipex.pipefd[0], STDIN_FILENO);
		if (ft_builtins_fork(*token))
			exit(SUCCESS);
		ft_pipex_exec(envp, l_token->content, *token, pipex);
		return (FAILURE);
	}
	else
	{
		if (ft_builtins(*token, envp) == 2)
			exit(EXIT_FAILURE);
	}
	ft_child_close_pipe(pipex);
	return (SUCCESS);
}
