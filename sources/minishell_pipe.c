/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:07:23 by agouet            #+#    #+#             */
/*   Updated: 2022/07/11 12:24:15 by agouet           ###   ########.fr       */
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

char	*get_paths_cmd(char *paths_i, char *cmd)
{
	char	*path_cmd;

	path_cmd = NULL;
	path_cmd = ft_strjoin(paths_i, "/");
	path_cmd = ft_strjoin_free(path_cmd, cmd);
	return (path_cmd);
}

int	ft_pipex_exec(char **envp, char *cmd, char **new_token_exec, t_pipe fds)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	paths = get_paths();
	ft_close_tmp(fds);
	if (cmd && (execve(cmd, new_token_exec, envp) == -1) && paths)
	{
		i = 0;
		while (paths[i])
		{
			path_cmd = get_paths_cmd(paths[i], cmd);
			if (access(path_cmd, F_OK) == 0)
			{
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

int	ft_pipex(t_list *l_token, char **args_exec, char ***envp, t_pipe pipex)
{
	if (pipex.ctrl == 1)
		ft_link_fd(pipex.pipefd[1], pipex.pipefd[0], STDIN_FILENO);
	if (pipe(pipex.pipefd) < 0)
		return (msg_perror("pipe"));
	ft_child(args_exec, envp, l_token, pipex);
	if (pipex.ctrl == 0)
		pipex.ctrl = 1;
	else
		pipex.ctrl = 0;
	monitoring_line(l_token->next->next, envp, pipex);
	return (0);
}
