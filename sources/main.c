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
		ft_write_fd("\n",1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	if (ac != 1)
		return (ft_write_fd("Usage : ./minishell\n", 1));
	signal(SIGINT, ft_new_prompt);
	line = readline("minishell> ");
	while (line != NULL)
	{
		add_history (line);
		minishell(line, env);
		ac = ft_is_exit(line);
		free(line);
		if (ac)
			break ;
		line = readline("minishell> ");
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
