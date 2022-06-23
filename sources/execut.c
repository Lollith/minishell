/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/06/23 11:55:33 by agouet           ###   ########.fr       */
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
		free(token);
}

char	**get_paths(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i] || ft_strncmp(envp[i], "PATH=", 5))
		paths = NULL;
	else
	{
		path = envp[i] + 5;
		paths = ft_split(path, ':');
	}
	return (paths);
}

char	*get_paths_cmd(char *paths_i, char *cmd)
{
	char	*path_cmd;

	path_cmd = NULL;
	path_cmd = ft_strjoin(paths_i, "/");
	path_cmd = ft_strjoin_free(path_cmd, cmd);
	return (path_cmd);
}

int	ft_child(char **new_token_exec, char **envp, t_list *l_token, t_pipe pipex)
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
		ft_exec(envp, l_token->content, new_token_exec, pipex);
		return (FAILURE);
	}
	if (pipex.pipefd[0] && pipex.ctrl == -1)
	{
		if (close(pipex.pipefd[0]) < 0)
			return (msg_perror("pipefd0.1 "));
		if (close(pipex.pipefd[1]) < 0)
			return (msg_perror("pipefd1.1 "));
		pipex.ctrl = 0;
	}
	return (SUCCESS);
}

int	ft_exec(char **envp, char *cmd, char **new_token_exec, t_pipe fds)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	paths = get_paths(envp);
	if (cmd && (execve(cmd, new_token_exec, envp) == -1) && paths)
	{
		i = 0;
		while (paths[i])
		{
			path_cmd = get_paths_cmd(paths[i], cmd);
			if (access(path_cmd, F_OK) == 0)
			{
				ft_close_tmp(fds);
				execve(path_cmd, new_token_exec, envp);
				ft_split_free(paths);
				exit (FAILURE);
			}
			i++;
			free(path_cmd);
		}
	}
	ft_split_free(paths);
	ft_msg(cmd, STDERR_FILENO);
	return (ft_msg(": Command not found.\n", STDERR_FILENO));
}
