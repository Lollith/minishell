/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:27:24 by agouet            #+#    #+#             */
/*   Updated: 2022/08/23 16:08:37 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipes(t_list *l_token, t_pipe *pipex)
{
	int		count_p;

	pipex->nb_pipes = 0;
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
}

void	parent2(char ***token, char ***envp, t_pipe *pipex)
{
	int	i;

	i = ft_builtins2(*token, envp, pipex);
	if (i == 2)
		ft_child_free(token, envp, 1);
	close(pipex->pipefd[pipex->act_p + 1][0]);
	close(pipex->pipefd[pipex->act_p + 1][1]);
	ft_child_close_pipe(pipex);
	if (*token != NULL)
		split_free_null(*token);
}
