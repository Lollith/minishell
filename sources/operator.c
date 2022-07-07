/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:15:29 by agouet            #+#    #+#             */
/*   Updated: 2022/07/07 17:44:00 by agouet           ###   ########.fr       */
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
		else if (ft_strncmp(l_token->next->content, ">", 1) == 0)
			ft_redir_out(l_token, args_exec, envp, pipex);
		else if (ft_strncmp(l_token->content, "<", 1) == 0)
			ft_redir_in(l_token, args_exec, envp, pipex);
	}
	else
	{
		pipex.ctrl = -1;
		ft_child(args_exec, envp, l_token, pipex);
	}
	return (ft_free_args_exec(args_exec, FAILURE));
}

int ft_eperluet(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	if (!ft_child(args_exec, envp, l_token, pipex))
		return (FAILURE);
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
int ft_redir_out(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	int fd;
	int fd_tmp;
	char *file;

	file = l_token->next->next->content;
	fd_tmp = dup(STDOUT_FILENO);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
	{
		perror(file);
		return (FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (ft_child(args_exec, envp, l_token, pipex) < 0)
		return (FAILURE);
	if (close(fd) < 0)
		return (msg_perror("fd "));
	if (dup2(fd_tmp, STDOUT_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (l_token->next->next->next)
		monitoring_line(l_token->next->next->next, envp, pipex);
	return (SUCCESS);
}
// cmd1 < file1 < file2 => result file2, si 1 existe pas => erreur file1 c tout
int ft_redir_in(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	int fd;
	int fd_tmp;
	char *file;
	//t_list *tmp_token;

	(void)args_exec;

	fd_tmp = dup(STDIN_FILENO);
	//tmp_token = (*l_token);
	//printf("recup ds redir cmd %s\n", (char *) (l_token)->content);
	printf("apre reorga 1em pos %s\n", (char *) (l_token)->content);
	printf("apre reorga 2em pos %s\n", (char *) (l_token)->next->content);
	printf("apre reorga 3em pos %s\n", (char *) (l_token)->next->next->content);
	file = args_exec[1];
	printf("%s\n", file);
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

	//	if (ft_child(args_exec, envp, l_token, pipex) < 0)
	// return (FAILURE);
	// if (dup2(fd_tmp, STDIN_FILENO) == -1)
	//	return (msg_perror("dup2 "));

	if ((l_token)->next->next)
		monitoring_line((l_token)->next->next, envp, pipex);
	return (SUCCESS);
}
