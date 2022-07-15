/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/07/11 12:19:27 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_return(char **envp)
{
	rl_clear_history();
	ft_split_free(envp);
	write(1, "\n", 1);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_list	*tmp_token;
	t_list	*l_token;
	t_pipe	pipex;

	if (!init(ac, av, &envp, &pipex))
		return (1);
	l_token = NULL;
	line = readline("minishell> ");
	while (line != NULL)
	{
		if (line[0])
		{
			list_token(&l_token, line);
			tmp_token = l_token;
			fd_monitor(tmp_token, &envp, &pipex);
			ft_lstclear2(&l_token);
		}
		free(line);
		if (ac == 2)
			break ;
		line = readline("minishell> ");
	}
	return (main_return(envp));
}
