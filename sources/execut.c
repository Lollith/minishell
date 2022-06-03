/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/06/02 15:25:10 by agouet           ###   ########.fr       */
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
}

char	**ft_is_flag(t_list *l_token)
{
	char	**new_token_exec;
	char	*cmd;
	int		size;

	cmd = l_token->content;

	if (l_token->next && ft_strchr(l_token->next->content, '-'))
		size = 3;
	else 
		size = 2;
	new_token_exec = (char **)malloc(sizeof(char *) * size);
	if (!new_token_exec)
		return (FAILURE);
	new_token_exec[0] = cmd;
	if (size == 3)
		new_token_exec[1] = l_token->next->content; 
	if (l_token->next && ft_strchr(l_token->next->content, '-'))
		ft_l_delete (l_token);
	new_token_exec[size - 1] = NULL;
	return (new_token_exec);
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
