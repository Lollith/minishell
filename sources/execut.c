/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:07:01 by agouet            #+#    #+#             */
/*   Updated: 2022/05/25 10:21:16 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_free_pa(char **paths, char *path_cmd, char *path_slash, char **token)
{
	free(path_cmd);
	free(paths);
	free(token);
	free(path_slash);
}

// execute une seule commande pour le moment token[0]
// access = 0 => check si une commande existe
// si exceve > 0 => n a pas marchee
int	ft_exec(char **envp, char **token)
{
	int		i;
	char	**paths;
	char	*path_cmd;
	char	*path_slash;

	i = 0;
	paths = get_paths(envp);
	while (paths[i])
	{
		path_slash = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(path_slash, token[0]);
		if (access(path_cmd, F_OK) == 0 && execve(path_cmd, token, envp))
		{
			ft_free_pa(paths, path_cmd, path_slash, token);
			return (FAILURE);
		}
		i++;
	}
	ft_free_pa(paths, path_cmd, path_slash, token);
	return (ft_msg("Erreur: CMD\n", 1));
}
