/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:57:26 by agouet            #+#    #+#             */
/*   Updated: 2022/07/11 12:19:40 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// SIGINT	=	ctrl + c
// SIGQUIT	=	ctrl + backslash
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

int	init(int ac, char **av, char ***envp, t_pipe *pipex)
{
	if (ft_main(ac, av, envp))
		return (FAILURE);
	pipex->ctrl = 0;
	pipex->pipefd[0] = 0;
	return (SUCCESS);
}

int	fd_monitor(t_list *tmp_token, char ***envp, t_pipe pipex)
{
	int	pid;
	int	wstatus;

	pipex.tmp_in = dup(STDIN_FILENO);
	pipex.tmp_out = dup(STDOUT_FILENO);
	monitoring_line(tmp_token, envp, pipex);
	pid = wait(&wstatus);
	while (pid > 0)
		pid = wait(&wstatus);
	if (dup2(pipex.tmp_in, STDIN_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (close(pipex.tmp_in) < 0)
		return (msg_perror("tmp_in "));
	if (dup2(pipex.tmp_out, STDOUT_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (close(pipex.tmp_out) < 0)
		return (msg_perror("tmp_out "));
	return (SUCCESS);
}
