/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:07:23 by agouet            #+#    #+#             */
/*   Updated: 2022/06/06 10:13:54 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a faire -> ds ft_child
// if ! child => if pipefd [0] existe => ft_link
// structure de pipefd
// rm file => a gerer
// path
/*

int ft_pipex(t_list *l_token,char **new_token_exec, char **envp)
{

    int pipefd[2];
    if (pipe(pipefd) < 0)
		return (msg_perror("pipe"));
    if(ft_exec(envp, l_token->content, new_token_exec) == 0)
        return (FAILURE);
    else
        monitoring_line(l_token->next->next, envp); 
    if (close(pipefd[0]) < 0)
		return (msg_perror("pipefd0 "));
	if (close(pipefd[1]) < 0)
		return (msg_perror("pipefd1 "));
	if (dup2(fdout_tmp, STDOUT_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (dup2(fdin_tmp, STDOUT_FILENO) == -1)
		return (msg_perror("dup2 "));
    return (SUCCESS);
}   

int ft_link_fd (int pipefd0, int pipefd1, int std) // std in / out
{
       
	int		fdout_tmp;
    int     fdin_tmp;

	fdout_tmp = dup(STDOUT_FILENO);// utile?
    fdin_tmp =dup(STDIN_FILENO);
    if (close(pipefd0) < 0)
        return (msg_perror("pipefd "));
    if (dup2(pipefd1, std) == -1)
		return (msg_perror("dup2 "));
    if (close(pipefd1) < 0)
		return (msg_perror("pipefd "));
    return (SUCCESS);
}

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
