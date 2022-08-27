/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lollith <lollith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/27 14:57:29 by lollith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

int	main_return(char **envp, t_pipe *pipex)
{
	rl_clear_history();
	ft_split_free(envp);
	write(1, "exit\n", 5);
	if (g_sig == 1)
		return (130);
	return (pipex->pipe_ret);
}

void	check_ret(t_pipe *pipex)
{
	if (g_sig == 1)
	{
		pipex->pipe_ret = 130;
		g_sig = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	char	*line;
	t_list	*l_token;
	t_pipe	pipex;

	if (!init(ac, av, &envp, &pipex))
		return (1);
	l_token = NULL;
	line = readline("minishell> ");
	while (line != NULL)
	{
		i = 0;
		check_ret(&pipex);
		while (ft_is_space(line[i], MS_SPACE))
			i++;
		if (line[i])
		{
			if (list_token(&l_token, line, &pipex))
				parent(l_token, &envp, &pipex);
			ft_lstclear3(&l_token);
		}
		free(line);
		line = readline("minishell> ");
	}
	return (main_return(envp, &pipex));
}
