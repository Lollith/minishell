/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/24 16:42:11 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_msg(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	return (FAILURE);
}

void	ft_new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_msg("\b\b  \n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		ft_msg("\b\b  \b\b", 1);
}

int	check_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (ft_msg("Error: path not found\n", 2));
	return (SUCCESS);
}

char	**lexer(char *line)
{
	char	**token;

	token = ft_split (line, ' ');
	if (!token)
		return (NULL);
	return (token);
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

void	ft_free_pa(char **paths, char *path_cmd, char *path_slash, char **token)
{
	free(path_cmd);
	free(paths);
	free(token);
	free(path_slash);
}

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

int	main(int ac, char **av, char **envp)
{
	char	**token;
	char	*line;

	(void)av;
	if (!check_env(envp))
		return (1);
	if (ac != 1)
		return (ft_msg("Usage : ./minishell\n", 1));
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, ft_new_prompt);
	line = readline("minishell> ");
	while (line != NULL)
	{
		add_history (line);
		minishell(line, envp);
		token = lexer(line);
		ft_exec(envp, token);
		free(line);
		line = readline("minishell> ");
	}
	rl_clear_history();
	return (ft_msg("\n", 1));
}
