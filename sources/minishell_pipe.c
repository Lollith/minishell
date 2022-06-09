/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:07:23 by agouet            #+#    #+#             */
/*   Updated: 2022/06/08 17:00:13 by agouet           ###   ########.fr       */
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
  //pid_t pid1;
  int status;
	if (pipex.ctrl == 1)
     ft_link_fd(pipex.pipefd[1], pipex.pipefd[0], STDIN_FILENO);
  if (pipe(pipex.pipefd) < 0)
	  return (msg_perror("pipe"));
  if (ft_child(new_token_exec,envp, l_token, pipex) < 0)
		return (FAILURE);
  
  else
  {
      pipex.ctrl = 1;
      monitoring_line(l_token->next->next, envp, pipex);
  }

  wait( &status);
  return (status);
}


 // pid1 = fork();// remplacer par ft_child
 // if (pid1 < 0)
  //  return (msg_perror("fork"));
  //else if (pid1 == 0)
 // {
  //  ft_link_fd(pipex.pipefd[0], pipex.pipefd[1], STDOUT_FILENO);
   // ft_exec(envp, l_token->content, new_token_exec);
		//free(new_token_exec);
 //   return (FAILURE);
 // }


    /*pid2 = fork();
    if (pid2 < 0)
      return (msg_perror("fork"));
    else if (pid2 == 0)
    {
      ft_link_fd(pipefd[1], pipefd[0], STDIN_FILENO);
      if (ft_exec(envp, l_token->next->next->content, new_token_exec) == 0)
        return (FAILURE);
    }*/
  //}
  //if (close(pipex.pipefd[0]) < 0)
  //  return (msg_perror("pipefd0. "));
  //if (close(pipex.pipefd[1]) < 0)
  //  return (msg_perror("pipefd1. "));
 // if (dup2(fdout_tmp, STDOUT_FILENO) == -1)
  //  return (msg_perror("dup2 "));
  //if (dup2(fdin_tmp, STDIN_FILENO) == -1)
    //return (msg_perror("dup2 "));

/*
int ft_link_fd1(int *pipefd)
{
    if (close(pipefd[0]) < 0)
        return (msg_perror("pipefd0 "));
    //printf("1\n");
    if (dup2(pipefd[1], STDOUT_FILENO) == -1)
    return (msg_perror("dup2 "));
    if (close(pipefd[1]) < 0)
    return (msg_perror("pipefd1 "));
    return (SUCCESS);
}

int ft_link_fd2(int *pipefd)
{
    printf ("pipe0 %d\n", pipefd[0]);
    if (close(pipefd[1]) < 0)
        return (msg_perror("pipefd1. "));
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
    return (msg_perror("dup2 "));
    if (close(pipefd[0]) < 0)
    return (msg_perror("pipefd0 "));
    return (SUCCESS);
}

*/