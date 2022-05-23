/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/19 15:14:23 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_fd(char *str, int fd)
{
	size_t	i;

	i = ft_strlen(str);
	write(fd, str, i);
	return (EXIT_SUCCESS);
}

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

int	main(int ac, char **av)
{
	char	*line;

	(void)av;
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
