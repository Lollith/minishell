/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/06/23 16:02:37 by agouet           ###   ########.fr       */
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

int	ft_child(char **new_token_exec, char ***envp, t_list *l_token, t_pipe pipex)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (-1);
	if (!child)
	{
		if ((pipex.ctrl == 0 || pipex.ctrl == 1) && pipex.pipefd[0])
			ft_link_fd(pipex.pipefd[0], pipex.pipefd[1], STDOUT_FILENO);
		if (pipex.pipefd[0] && pipex.ctrl == -1)
			ft_link_fd(pipex.pipefd[1], pipex.pipefd[0], STDIN_FILENO);
		if (ft_builtins(l_token->content, envp) == 0)
			ft_pipex_exec(*envp, l_token->content, new_token_exec, pipex);
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
	return (ft_builtins_ret(l_token->content, envp));
}

int	ft_old_child(char **paths, char *path_cmd, char **token, char **envp)
{
	pid_t	child;
	int		wstatus;

	child = fork();
	if (child < 0)
		return (FAILURE);
	if (!child)
	{
		execve(path_cmd, token, envp);
		ft_free_pa(paths, path_cmd, token);
		return (FAILURE);
	}
	wait(&wstatus);
	return (SUCCESS);
}

int	ft_exec(char **envp, char *cmd, char **new_token_exec)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	paths = get_paths();
	path_cmd = NULL;
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin_free(path_cmd, cmd);
		if (access(path_cmd, F_OK) == 0)
		{
			if (ft_old_child(paths, path_cmd, new_token_exec, envp))
			{
				free(path_cmd);
				return (SUCCESS);
			}
		}
		free(path_cmd);
		i++;
	}
	ft_free_pa(paths, path_cmd, new_token_exec);
	ft_msg(cmd, STDERR_FILENO);
	return (ft_msg(": Command not found.\n", STDERR_FILENO));
}
