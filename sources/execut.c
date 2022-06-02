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

// recup le chemin dune commande
// paths a free
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

// cette fonction permet de creer un touble tableau de char cmd+NULL 
// pour que execve ne confonde pas le && pour le flag
// a faire : gerer les flags
char	**create_token_exec(t_list *l_token)
{
	char	**new_token_exec;
	int		i;
	char	*cmd;

	cmd = l_token->content;
	i = 0;
	new_token_exec = (char **)malloc(sizeof(char *) * 3);
	if (!new_token_exec)
		return (FAILURE);
	new_token_exec[i] = cmd;
	if (l_token->next->content && ft_strchr(l_token->next->content, '-'))
	{
		new_token_exec[i + 1] = l_token->next->content; 
		i++;
	}
	new_token_exec[i + 1] = NULL;

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
