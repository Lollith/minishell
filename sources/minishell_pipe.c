/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:07:23 by agouet            #+#    #+#             */
/*   Updated: 2022/06/10 16:48:28 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_link_fd(int pipefd0, int pipefd1, int std) // std in / out
{
  if (close(pipefd0) < 0)
    return (msg_perror("pipefd0 "));
  if (dup2(pipefd1, std) == -1)
    return (msg_perror("dup2 "));
  if (close(pipefd1) < 0)
    return (msg_perror("pipefd1 "));
  return (SUCCESS);
}
// ls | wc |wc -l =1
int ft_pipex(t_list *l_token, char **new_token_exec, char **envp, t_pipe pipex)
{
  if (pipex.ctrl == 1) // avant pipe
     ft_link_fd(pipex.pipefd[1], pipex.pipefd[0], STDIN_FILENO);// sert?
  if (pipe(pipex.pipefd) < 0)
	  return (msg_perror("pipe"));
  if (ft_child(new_token_exec,envp, l_token, pipex) <= 0)
		return (FAILURE);
  
  else
  {
     if (pipex.ctrl == 0) 
        pipex.ctrl = 1;
     else
        pipex.ctrl = 0;
    monitoring_line(l_token->next->next, envp, pipex);
  }

  return (0);
}