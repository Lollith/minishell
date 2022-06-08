/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/06 10:04:23 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_main(int ac, char **av, char **envp)
{
	(void)av;
	if (!check_env(envp))
	{
		ft_msg("No environment found\n", 1);
		return (1);
	}
	if (ac != 1)
	{
		ft_msg("Usage : ./minishell\n", 1);
		return (1);
	}
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, ft_new_prompt);
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*line;
// 	t_list	*l_token;
// 	t_list	*tmp_token;

// 	if (ft_main(ac, av, envp))
// 		return (1);
// 	l_token = NULL;
// 	line = readline("minishell> ");
// 	while (line != NULL)
// 	{
// 		add_history (line);
// 		ac = minishell(line, envp);
// 		if (!list_token(&l_token, line))
// 			return (1);
// 		tmp_token = l_token;
// 		ac = minishell(line, envp);
// 		monitoring_line(tmp_token, envp);
// 		ft_lstclear2(&l_token);
// 		free(line);
// 		if (ac == 2)
// 			break ;
// 		line = readline("minishell> ");
// 	}
// 	rl_clear_history();
// 	return (ft_msg("\n", 1));
// }
