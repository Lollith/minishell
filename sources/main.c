/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/14 10:26:53 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SIGQUIT	=	ctrl + \
// SIGINT	=	ctrl + c
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
		return (ft_msg("Error : Path not found\n", 2));
	return (SUCCESS);
}

int	ft_main(int ac, char **av, char ***envp)
{
	(void)av;
	if (ac != 1)
	{
		ft_msg("Usage : ./minishell\n", 1);
		return (1);
	}
	if (!*envp)
	{
		ft_msg("Error : No environment found\n", 1);
		return (1);
	}
	if (!check_env(*envp))
		return (1);
	*envp = ft_realloc_envp(*envp);
	if (!*envp)
		return (1);
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, ft_new_prompt);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;

	if (ft_main(ac, av, &envp))
		return (1);
	line = readline("minishell> ");
	while (line != NULL)
	{
		add_history(line);
		ac = minishell(line, &envp);
		free(line);
		if (ac == 2)
			break ;
		line = readline("minishell> ");
	}
	if (line == NULL)
		ft_msg("exit", 1);
	rl_clear_history();
	ft_split_free(envp);
	return (ft_msg("\n", 1));
}
