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

int	parent(t_list *tmp_token, char ***envp, t_pipe *pipex)
{
	int	pid;
	int	wstatus;

	wstatus = 0;
	pipex->tmp_in = dup(STDIN_FILENO);
	pipex->tmp_out = dup(STDOUT_FILENO);
	if (monitoring_line(tmp_token, envp, pipex) == 0)
		pipex->pipe_ret = 1;
	else
		pipex->pipe_ret = -1;
	if (pipex->pipe_ret != 1)
		ft_pipe_ret(pipex);
	pid = wait(&wstatus);
	while (pid > 0)
		pid = wait(&wstatus);
	dup2(pipex->tmp_in, STDIN_FILENO);
	close(pipex->tmp_in);
	dup2(pipex->tmp_out, STDOUT_FILENO);
	close(pipex->tmp_out);
	return (SUCCESS);
}

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
			if (list_token(&l_token, line))
			{	
				tmp_token = l_token;
				parent(tmp_token, &envp, &pipex);
			}
			ft_lstclear2(&l_token);
		}
		free(line);
		line = readline("minishell> ");
	}
	return (main_return(envp));
}
