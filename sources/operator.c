/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:15:29 by agouet            #+#    #+#             */
/*   Updated: 2022/07/11 12:03:43 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int monitoring_line(t_list *l_token, char **envp, t_pipe pipex)
{
	char **args_exec;

	reorganize(&l_token);
	args_exec = ft_is_arg(l_token);
	if (l_token->next)
	{
		if (ft_strncmp(l_token->next->content, "&&", 2) == 0)
			ft_eperluet(l_token, args_exec, envp, pipex);
		else if (ft_strncmp(l_token->next->content, "||", 2) == 0)
			ft_ou(l_token, args_exec, envp, pipex);
		else if (ft_strncmp(l_token->next->content, "|", 1) == 0)
			ft_pipex(l_token, args_exec, envp, pipex);
		else if (ft_strncmp(l_token->content, ">", 1) == 0)
			ft_redir_out(l_token, args_exec, envp, pipex);
		else if (ft_strncmp(l_token->content, "<", 1) == 0)
			ft_redir_in(l_token, args_exec, envp, pipex);
	}
	else
	{
		pipex.ctrl = -1;
		if (ft_child(args_exec, envp, l_token, pipex) == 0)
			return (FAILURE);
	}
	return (ft_free_args_exec(args_exec, FAILURE));
}

int ft_eperluet(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	if (ft_child(args_exec, envp, l_token, pipex) == 0)
		exit (FAILURE);
	else
		monitoring_line(l_token->next->next, envp, pipex);
	return (SUCCESS);
}

int ft_ou(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	if (ft_child(args_exec, envp, l_token, pipex) > 0)
		return (SUCCESS);
	else
		monitoring_line(l_token->next->next, envp, pipex);
	return (FAILURE);
}

// > file => creer file
// > file ls  = ls > file
// ls > file1 > file2: creer les 2 files , ecrase f1 et f2 + \n fd file2
// echo test > file test1  = exho test test1 > file
//bad cmd > file  : crer file ms erreur cmd
int ft_redir_out(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	int fd;
	int fd_tmp;
	char *file;

	fd_tmp = dup(STDOUT_FILENO);
	file = args_exec[1]; // cas ou file  existe
	if (!file)// ca ou file exsite pas deja
	{
		file = l_token->next->content;
		ft_l_delete(l_token); // attention supression de mon file de ma liste chainee, pas remise ds un tab
	}
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
	{
		perror(file);
		return (FAILURE);
	}
	if (l_token->next)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (msg_perror("dup2 "));
		if (close(fd) < 0)
			return (msg_perror("fd. "));
		monitoring_line(l_token->next, envp, pipex);
	}
	close(fd);
	return (SUCCESS);
}
// bash : cmd1 < file1 < file2 => result file2, si 1 existe pas => erreur file1 c tout
//=> < (-file1) cmd < (-file2)
//=> < (-file1) < (-file2) cmd1
int ft_redir_in(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	int fd;
	int fd_tmp;
	char *file;

	(void)args_exec;

	fd_tmp = dup(STDIN_FILENO);
	file = args_exec[1];
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		return (FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (close(fd) < 0)
		return (msg_perror("fd "));
	if ((l_token)->next)
		monitoring_line((l_token)->next, envp, pipex);
	return (SUCCESS);
}
