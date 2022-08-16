/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:07:23 by agouet            #+#    #+#             */
/*   Updated: 2022/08/16 13:24:51 by agouet           ###   ########.fr       */
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

int	ft_pipex_return(char **paths, t_list *list, t_pipe *pipex, char **exec)
{
	char	*cmd;

	cmd = list->content;
	ft_free_args_exec(exec, 0);
	ft_split_free(paths);
	ft_msg(cmd, STDERR_FILENO);
	ft_msg(": Command not found.\n", STDERR_FILENO);
	if (pipex->l_start)
		ft_lstclear2(&pipex->l_start);
	return (FAILURE);
}

int	ft_pipex_exec(char ***envp, t_list *list, char **token_exec, t_pipe *fds)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	paths = get_paths(*envp);
	ft_close_tmp(fds);
	if (list->content && (execve(list->content, token_exec, *envp) == -1) && \
	paths)
	{
		i = -1;
		while (paths[++i])
		{
			path_cmd = get_paths_cmd(paths[i], list->content);
			if (access(path_cmd, F_OK) == 0)
			{
				execve(path_cmd, token_exec, *envp);
				ft_lstclear2(&fds->l_start);
				ft_split_free(token_exec);
				ft_split_free(paths);
				exit(FAILURE);
			}
			free(path_cmd);
		}
	}
	return (ft_pipex_return(paths, list, fds, token_exec));
}

int	ft_pipex(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	//if ((pipex->ctrl == 1) && pipex->pipefd[1] != -1)
	//	{
		//	ft_link_fd(pipex->pipefd[1], pipex->pipefd[0], STDIN_FILENO);
		//dup2(pipex->pipefd[0], STDIN_FILENO);
	//	close(pipex->pipefd[1]);
	//	close (pipex->pipefd[0]);
	//	}
	if (pipe(pipex->pipefd) < 0)
		return (msg_perror("pipe"));
	ft_child(&args_exec, envp, l_token, pipex);
	if (pipex->ctrl == 0)
		pipex->ctrl = 1;
	else
		pipex->ctrl = 0;
	if (monitoring(l_token, l_token->next->next, envp, pipex) == 0)
		return (FAILURE);
	ft_split_free(args_exec);
	return (SUCCESS);
}
