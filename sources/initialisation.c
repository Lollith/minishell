/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:57:26 by agouet            #+#    #+#             */
/*   Updated: 2022/08/02 11:38:43 by agouet           ###   ########.fr       */
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
	pipex->pid = 0;
	pipex->pipe_ret = -1;
	pipex->ctrl = 0;
	pipex->pipefd[0] = 0;
	return (SUCCESS);
}

// >128 when a command was ended by a signal.
// The value is 128 plus the signal number.
