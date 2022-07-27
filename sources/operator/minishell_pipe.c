/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:07:23 by agouet            #+#    #+#             */
/*   Updated: 2022/07/27 11:41:29 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close_tmp(t_pipe *pipex)
{
	close(pipex->tmp_in);
	close(pipex->tmp_out);
	return (SUCCESS);
}

char	*get_paths_cmd(char *paths_i, char *cmd)
{
	char	*path_cmd;

	path_cmd = NULL;
	path_cmd = ft_strjoin(paths_i, "/");
	path_cmd = ft_strjoin_free(path_cmd, cmd);
	return (path_cmd);
}

int	ft_pipex_exec_return(char **paths, char *cmd)
{
	ft_split_free(paths);
	ft_msg(cmd, STDERR_FILENO);
	ft_msg(": Command not found.\n", STDERR_FILENO);
	return (FAILURE);
}

int	ft_pipex_exec(char ***envp, char *cmd, char **token_exec, t_pipe *fds)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	paths = get_paths();
	ft_close_tmp(fds);
	if (cmd && (execve(cmd, token_exec, *envp) == -1) && paths)
	{
		i = 0;
		while (paths[i])
		{
			path_cmd = get_paths_cmd(paths[i], cmd);
			if (access(path_cmd, F_OK) == 0)
			{
				execve(path_cmd, token_exec, *envp);
				ft_split_free(paths);
				exit(FAILURE);
			}
			i++;
			free(path_cmd);
		}
	}
	return (ft_pipex_exec_return(paths, cmd));
}

int	ft_pipex(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	if (pipex->ctrl == 1)
		ft_link_fd(pipex->pipefd[1], pipex->pipefd[0], STDIN_FILENO);
	if (pipe(pipex->pipefd) < 0)
		return (msg_perror("pipe"));
	ft_child(&args_exec, envp, l_token, pipex);
	if (pipex->ctrl == 0)
		pipex->ctrl = 1;
	else
		pipex->ctrl = 0;
	if (monitoring_line(l_token->next->next, envp, pipex) == 0)
		return (FAILURE);
	return (SUCCESS);
}
