/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lollith <lollith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:07:23 by agouet            #+#    #+#             */
/*   Updated: 2022/08/21 19:33:47 by lollith          ###   ########.fr       */
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

int	ft_pipex_return(char **paths, t_list *list, t_pipe *pipex)
{
	char	*cmd;

	cmd = list->content;
	ft_split_free(paths);
	if (!ft_is_str(cmd, "<") && !ft_is_str(cmd, ">"))
	{
		ft_msg("minishell: \'", STDERR_FILENO);
		ft_msg(cmd, STDERR_FILENO);
		ft_msg("\': Command not found.\n", STDERR_FILENO);
	}
	if (pipex->ctrl_redir2 == 1)
	{
		pipex->ctrl_redir2 = 0;
		if (list != NULL)
			ft_lstclear3(&list);
	}
	else
	{
		if (pipex->l_start != NULL)
			ft_lstclear3(&pipex->l_start);
	}
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
				split_free_null(token_exec);
				ft_split_free(paths);
				exit(FAILURE);
			}
			free(path_cmd);
		}
	}
	return (ft_pipex_return(paths, list, fds));
}

int	ft_pipex(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	if (pipe(pipex->pipefd) < 0)
		return (ft_msg_perror("pipe"));
	ft_child(&args_exec, envp, l_token, pipex);
	if (pipex->ctrl == 0)
		pipex->ctrl = 1;
	else
		pipex->ctrl = 0;
	if (monitoring(l_token, l_token->next->next, envp, pipex) == 0)
		return (FAILURE);
	return (SUCCESS);
}
