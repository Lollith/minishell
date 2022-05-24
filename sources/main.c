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

int	ft_is_exit(char *s)
{
	int		i;
	char	*exit;

	if (ft_strlen(s) != 4)
		return (0);
	exit = "exit";
	i = 0;
	while (exit[i] && s[i] == exit[i])
		i++;
	if (!exit[i] && !s[i])
		return (1);
	return (0);
}

void	ft_new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		ft_msg("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
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

char 	**lexer (char *line)
{
	char	**token;

	token = ft_split (line, ' ');
	if (!token)
		return (NULL);
	
	return (token); // a free

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
	return (paths);  // a free
}

int	ft_exec(char **envp, char **token)
{
	char	**paths;
	char	*path_cmd;
	char	*path_slash;
	int		i;

	i = 0;
	paths = get_paths(envp);
	while (paths[i])
	{
		path_slash = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(path_slash, token[0]); // 0 car pour une seule commande pour le moment
		if(access(path_cmd, F_OK) == 0) // si commande  existe
		{
			if (execve(path_cmd, token, envp)) // si exceve >  0 =na  pas marcher
			{
				free(path_cmd);
				free(paths);
				free(token);
				free(path_slash);
				return (FAILURE);
			}
		}	
		i++;
	}
	free(path_cmd);
	free(paths);
	free(token);
	free(path_slash);
	return (ft_msg("Erreur: CMD\n", 1));
}
//ft fork pour que chaque commande soit ouverte ds un enfant  et ne pas quiter le shell
//void ft_fork


//void	look_for_operator(char **taken, char **av, char **envp)

int	main(int ac, char **av, char **envp)
{
	char	**token;// pour test
	char	*line;

	(void)av;
	if (!check_env(envp))
		return (1);
	if (ac != 1)
		return (ft_msg("Usage : ./minishell\n", 1));
	signal(SIGINT, ft_new_prompt);
	line = readline("minishell> ");
	while (line != NULL)
	{
		add_history (line);
		minishell(line, envp);


		token = lexer(line);// pour test
		ft_exec(envp, token);// pour test

		ac = ft_is_exit(line);
		free(line);
		if (ac)
			break ;
		line = readline("minishell> ");
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
