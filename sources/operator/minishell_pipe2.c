/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:27:24 by agouet            #+#    #+#             */
/*   Updated: 2022/08/18 16:44:09 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_pipes(t_pipe *pipex)
{
	int		count_p;

	count_p = 0;
	if (pipex->l_start != NULL)
	{
		while (pipex->l_start != NULL)
		{
			if ( ft_strncmp(pipex->l_start->content, "|", 2) == 0)
				count_p++;
			pipex->l_start = pipex->l_start->next;
		}
	}
	return (count_p);
}

void	parent2(char ***token, char ***envp, t_pipe *pipex)
{

(void)(token);
(void) envp;
	//if (pipex->pipefd[1] != -1 && ft_count_pipes (pipex) > 1)
	ft_link_fd(pipex->pipefd[1], pipex->pipefd[0], STDIN_FILENO);
	ft_child_close_pipe(pipex);
}
