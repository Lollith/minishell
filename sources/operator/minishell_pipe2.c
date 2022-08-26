/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:27:24 by agouet            #+#    #+#             */
/*   Updated: 2022/08/26 13:03:21 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_std(t_pipe *pipex)
{
	dup2(pipex->tmp_in, STDIN_FILENO);
	if (pipex->tmp_in > -1)
		close(pipex->tmp_in);
	dup2(pipex->tmp_out, STDOUT_FILENO);
	if (pipex->tmp_out > -1)
		close(pipex->tmp_out);
}

void	count_pipes(t_list *l_token, t_pipe *pipex)
{
	int	count_p;

	pipex->nb_pipes = 0;
	pipex->nb_pipes_const = 0;
	count_p = 0;
	if (l_token != NULL)
	{
		while (l_token != NULL)
		{
			if (ft_strncmp(l_token->content, "|", 2) == 0)
				count_p++;
			l_token = l_token->next;
		}
	}
	pipex->nb_pipes = count_p;
	pipex->nb_pipes_const = count_p;
}

void	parent2(char ***token, char ***envp, t_pipe *pipex)
{
	int	i;

	i = ft_builtins2(*token, envp, pipex);
	if (i == 2)
		ft_child_free(token, envp, 1);
	if (pipex->nb_pipes_const > 1)
	{
		if (pipex->pipefd[pipex->act_p + 1][0] > -1)
			close(pipex->pipefd[pipex->act_p + 1][0]);
		if (pipex->pipefd[pipex->act_p + 1][1] > -1)
			close(pipex->pipefd[pipex->act_p + 1][1]);
	}
	ft_child_close_pipe(pipex);
	if (*token != NULL)
		split_free_null(*token);
	pipex->ctrl_redir2 = 0;
}
