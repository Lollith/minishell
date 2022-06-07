/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:07:23 by agouet            #+#    #+#             */
/*   Updated: 2022/06/07 15:17:17 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a faire -> ds ft_child
// if ! child => if pipefd [0] existe => ft_link
// structure de pipefd

int ft_link_fd (int pipefd0, int pipefd1, int std) // std in / out
{
    if (close(pipefd0) < 0)
        return (msg_perror("pipefd0 "));
    if (dup2(pipefd1, std) == -1)
		  return (msg_perror("dup2 "));
    if (close(pipefd1) < 0)
		  return (msg_perror("pipefd1 "));
    return (SUCCESS);
}

int ft_exec_pipe(char **envp, char *cmd, char **new_token_exec)
{
  int		i;
	char	**paths;
	char	*path_cmd;

	paths = get_paths(envp);
	path_cmd = NULL;
  i = 0;
  while (paths[i])
  {
    
		path_cmd = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin_free(path_cmd, cmd);
    if(access(path_cmd, F_OK) == 0)
    {
		  execve(path_cmd, new_token_exec, envp);
		  ft_free_pa(paths, path_cmd, new_token_exec);
	  	return (FAILURE);
    }
    i++;
  }
	ft_free_pa(paths, path_cmd, new_token_exec);
	ft_msg(cmd, 1);
	return (ft_msg(": Command not found.\n", 1));
}

int ft_pipex(t_list *l_token,char **new_token_exec, char **envp)
{

	  int     fdout_tmp;
    int     fdin_tmp;
   //t_data  fds;
    int     pipefd[2];
    pid_t   pid1;
    int status;

  	fdout_tmp = dup(STDOUT_FILENO);
    fdin_tmp = dup(STDIN_FILENO);
    if (pipe(pipefd) < 0)
		  return (msg_perror("pipe"));
    pid1 = fork();
  	if (pid1 < 0)
		  return (msg_perror("fork"));
  	else if (pid1 == 0)
    {
      ft_link_fd(pipefd[0], pipefd[1], STDOUT_FILENO);
      if(ft_exec_pipe(envp, l_token->content, new_token_exec) == 0)
        return (FAILURE);
    }
    else
    {
      ft_link_fd(pipefd[1], pipefd[0], STDIN_FILENO);
      monitoring_line(l_token->next->next, envp); 
    }
   // if (close(pipefd[0]) < 0)
  	//	return (msg_perror("pipefd0. "));
  //	if (close(pipefd[1]) < 0)
  	//	return (msg_perror("pipefd1. "));
  	if (dup2(fdout_tmp, STDOUT_FILENO) == -1)
  		return (msg_perror("dup2 "));
  	if (dup2(fdin_tmp, STDOUT_FILENO) == -1)
  		return (msg_perror("dup2 "));
    waitpid(pid1, &status, 0);
    return (status);
}   


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