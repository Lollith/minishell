/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:57:26 by agouet            #+#    #+#             */
/*   Updated: 2022/08/18 10:15:02 by agouet           ###   ########.fr       */
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
		g_sig = 1;
	}
	else if (signum == SIGQUIT)
		ft_msg("\b\b  \b\b", 1);
}

void	signal_here_doc(int signum)
{
	if (signum == SIGINT)
	{
		g_sig = 1;
		ft_msg("\b\b  \n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		close(0);
	}
}

int	check_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
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
	pipex->l_start = NULL;
	pipex->pid = 0;
	pipex->pipe_ret = -1;
	pipex->ctrl = 0;
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	pipex->ctrl_redir = 0;
	return (SUCCESS);
}

// >128 when a command was ended by a signal.
// The value is 128 plus the signal number.
