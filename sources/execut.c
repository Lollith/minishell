/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/06/08 16:59:28 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pa(char **paths, char *path_cmd, char **token)
{
	if (paths)
		free(paths);
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

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	path = envp[i] + 5;
	paths = ft_split(path, ':');
	return (paths);
}

int	ft_child(char **new_token_exec, char **envp, t_list *l_token, t_pipe pipex)
{
	pid_t	child;
	int		wstatus;
	int fdin_tmp;
	int fdout_tmp;
	

  	fdout_tmp = dup(STDOUT_FILENO);
  	fdin_tmp = dup(STDIN_FILENO);
	child = fork();
	if (child < 0)
		return (FAILURE);
	if (!child)
	{
		if (pipex.ctrl == 1)
   	 	  	ft_link_fd(pipex.pipefd[1], pipex.pipefd[0], STDIN_FILENO);
		if (pipex.ctrl == 0 && pipex.pipefd[0])
  		  	ft_link_fd(pipex.pipefd[0], pipex.pipefd[1], STDOUT_FILENO);
		ft_exec(envp, l_token->content, new_token_exec);
		//free(new_token_exec);
		return (FAILURE);
	}
	if (pipex.ctrl == 1)
	{
 			 if (close(pipex.pipefd[0]) < 0) // mettre ds une fct
			    return (msg_perror("pipefd0.1 "));
			if (close(pipex.pipefd[1]) < 0)
			    return (msg_perror("pipefd1.1 "));
  			if (dup2(fdin_tmp, STDIN_FILENO) == -1)
    			return (msg_perror("dup2 "));
  			if (dup2(fdout_tmp, STDOUT_FILENO) == -1)
 			   return (msg_perror("dup2 "));
			pipex.ctrl = 0;
	}
	wait(&wstatus);
	return (SUCCESS);
}

// access = 0 => check si une commande existe
// si exceve > 0 => n a pas marchee
int	ft_exec(char **envp, char *cmd, char **new_token_exec)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	paths = get_paths(envp);
	path_cmd = NULL;
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin_free(path_cmd, cmd);// attention leaks
		if (access(path_cmd, F_OK) == 0)
		{
			 execve(path_cmd, new_token_exec, envp);
			free(paths);
			free(path_cmd);
			return (FAILURE);
		}
		i++;
	}
	free(paths);
	free(path_cmd);
	ft_msg(cmd, 1);
	return (ft_msg(": Command not found.\n", 1));
}



/*
int	ft_child(char **paths, char *path_cmd, char **new_token_exec, char **envp)
{
	pid_t	child;
	int		wstatus;

	child = fork();
	if (child < 0)
		return (FAILURE);
	if (!child)
	{
		execve(path_cmd, new_token_exec, envp);
		ft_free_pa(paths, path_cmd, new_token_exec);
		return (FAILURE);
	}
	wait(&wstatus);
	return (wstatus);
}int	ft_exec(char **envp, char *cmd, char **new_token_exec)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	paths = get_paths(envp);
	path_cmd = NULL;
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin_free(path_cmd, cmd);
		if (access(path_cmd, F_OK) == 0)
		{
			if (ft_child(paths, path_cmd, new_token_exec, envp) >= 0)
				return (SUCCESS);
		}
		i++;
	}
	ft_free_pa(paths, path_cmd, new_token_exec);
	ft_msg(cmd, 1);
	return (ft_msg(": Command not found.\n", 1));
}
*/