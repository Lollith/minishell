/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/06/06 15:35:59 by agouet           ###   ########.fr       */
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

char	**ft_is_arg(t_list *l_token) // too long
{
	char		**args_exec;
	int			size;
	struct stat	info;
	int			i;
	t_list		*tmp_token;

	tmp_token = l_token;
	i = 1;
	size = 2;
	while ((tmp_token->next && (ft_strchr(tmp_token->next->content, '-')
				|| (stat(tmp_token->next->content, &info) == 0))))
	{
		size++;
		tmp_token = tmp_token->next;
	}
	args_exec = (char **)malloc(sizeof(char *) * size);
	if (!args_exec)
		return (FAILURE);
	args_exec[0] = l_token->content;
	while (l_token && i < size - 1)
	{
		args_exec[i] = l_token->next->content;
		i++;
		ft_l_delete (l_token);
	}
	args_exec[size - 1] = NULL;
	return (args_exec);
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
