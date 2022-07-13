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
	if (!path)
		return (NULL);
	res = ft_split(path, ':');
	if (!res)
		return (NULL);
	return (res);
}

// change $VAR , $? and * here
int	ft_child(char **new_token_exec, char ***envp, t_list *l_token, t_pipe pipex)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (FAILURE);
	if (!child)
	{
		if ((pipex.ctrl == 0 || pipex.ctrl == 1) && pipex.pipefd[0])
			ft_link_fd(pipex.pipefd[0], pipex.pipefd[1], STDOUT_FILENO);
		if (pipex.pipefd[0] && pipex.ctrl == -1)
			ft_link_fd(pipex.pipefd[1], pipex.pipefd[0], STDIN_FILENO);
		if (ft_builtins(new_token_exec, envp))
			exit(SUCCESS);
		ft_pipex_exec(envp, l_token->content, new_token_exec, pipex);
		return (FAILURE);
	}
	if (pipex.pipefd[0] && pipex.ctrl == -1)
	{
		close(pipex.pipefd[0]);
		close(pipex.pipefd[1]);
		pipex.ctrl = 0;
	}
	return (SUCCESS);
}
