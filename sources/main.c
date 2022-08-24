/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:14:21 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/24 11:06:22 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	ft_ret1(t_pipe *pipex)
{
	if (pipex->pipe_ret != 1)
		ft_pipe_ret(pipex);
	if (pipex->pipe_ret_b != -1)
		pipex->pipe_ret = pipex->pipe_ret_b;
}

int	parent(t_list *l_token, char ***envp, t_pipe *pipex)
{
	int	pid;
	int	wstatus;

	wstatus = 0;
	pipex->tmp_in = dup(STDIN_FILENO);
	pipex->tmp_out = dup(STDOUT_FILENO);
	if (!next_checker(l_token))
		return (FAILURE);
	count_pipes(l_token, pipex);
	if (monitoring(l_token, l_token, envp, pipex) == 0)
		pipex->pipe_ret = 1;
	else
		pipex->pipe_ret = -1;
	ft_ret1(pipex);
	pid = wait(&wstatus);
	while (pid > 0)
		pid = wait(&wstatus);
	if (g_sig == 1)
		pipex->pipe_ret = 130;
	clean_std(pipex);
	signal(SIGINT, ft_new_prompt);
	signal(SIGQUIT, ft_new_prompt);
	return (SUCCESS);
}

void	ft_pipe_ret(t_pipe *pipex)
{
	int	wstatus;

	wstatus = 0;
	waitpid(pipex->pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		pipex->pipe_ret = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		pipex->pipe_ret = 128 + WTERMSIG(wstatus);
	else
		pipex->pipe_ret = 0;
}

int	main_return(char **envp, t_pipe *pipex)
{
	rl_clear_history();
	ft_split_free(envp);
	write(1, "exit\n", 5);
	if (g_sig == 1)
		return (130);
	return (pipex->pipe_ret);
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
		g_sig = 0;
		i = 0;
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
