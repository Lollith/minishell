/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/24 10:33:21 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// faire un choix entre c 2 fct et entre nos retrun EXIT ou failure--------------------------------------------

int	ft_write_fd(char *str, int fd)
{
	size_t	i;

	i = ft_strlen(str);
	write(fd, str, i);
	return (EXIT_SUCCESS);//0
}

int	msg_error(char *error)
{
	write(STDERR_FILENO, error, ft_strlen (error));
	return(FAILURE);//0
}

//-------------------------------------------------------------------




// going to be useless when adding execve
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

// check si la variable PATH existe//
int	check_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if(!envp[i])
		return(msg_error("Error: path not found\n"));// 0
	return (SUCCESS); // 1
}

int	main(int ac, char **av, char **envp)
{
	char	*line;

	(void)av;
	if (!check_env(envp))
		return (1);
	if (ac != 1)
		return (ft_write_fd("Usage : ./minishell\n", 1));
	
	line = readline("minishell> ");
	while (line != NULL)
	{
		add_history (line);
		printf("%s\n", line);// minishell function go here
		ac = ft_is_exit(line);// going to be useless when adding execve
		free(line);
		if (ac)// going to be useless when adding execve
			break ;// going to be useless when adding execve
		line = readline("minishell> ");
	}
	return (EXIT_SUCCESS);
}
