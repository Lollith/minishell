/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:15:29 by agouet            #+#    #+#             */
/*   Updated: 2022/06/17 16:36:53 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	monitoring_line(t_list *l_token, char **envp, t_pipe pipex)
{
	char	**args_exec;

	args_exec = ft_is_arg(l_token);
	if (l_token->next)
	{
		if (ft_strncmp(l_token->next->content, "&&", 2) == 0)
			ft_eperluet(l_token, args_exec, envp, pipex);
		else if (ft_strncmp(l_token->next->content, "||", 2) == 0)
			ft_ou(l_token, args_exec, envp, pipex);
		else if (ft_strncmp(l_token->next->content, "|", 1) == 0)
			ft_pipex(l_token, args_exec, envp, pipex);
		else if (ft_strncmp(l_token->next->content, ">", 1) == 0
			|| ft_strncmp(l_token->next->content, ">|", 2) == 0)
			ft_redir_out(l_token, args_exec, envp, pipex);
		else if (ft_strncmp(l_token->next->content, "<", 1) == 0)
			ft_redir_in(l_token, args_exec, envp, pipex);
	}
	else
	{
		pipex.ctrl = -1;
		if (ft_child(args_exec, envp, l_token, pipex) >= 0)
		{
			free(args_exec);
			return (SUCCESS);
		}
	}
	free(args_exec);
	return (FAILURE);
}

int	ft_eperluet(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	if (!ft_child(args_exec, envp, l_token, pipex))
		return (FAILURE);
	else
		monitoring_line(l_token->next->next, envp, pipex);
	return (SUCCESS);
}

int	ft_ou(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	if (ft_child(args_exec, envp, l_token, pipex) > 0)
		return (SUCCESS);
	else
		monitoring_line(l_token->next->next, envp, pipex);
	return (FAILURE);
}

int	ft_redir_out(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	int		fd;
	int		fd_tmp;
	char	*file;

	file = l_token->next->next->content;
	fd_tmp = dup(STDOUT_FILENO);
	fd = open (file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		return (msg_perror("open "));
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

int	ft_redir_in(t_list *l_token, char **args_exec, char **envp, t_pipe pipex)
{
	int			fd;
	int			fd_tmp;
	char		*file;
	struct stat	info;

	if (stat(l_token->next->content, &info) == 0)
		file = l_token->next->content;
	else
		file = l_token->next->next->content;
	fd_tmp = dup(STDIN_FILENO);
	fd = open (file, O_RDONLY);
	if (fd < 0)
		return (msg_perror("open "));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (ft_child(args_exec, envp, l_token, pipex) < 0)
		return (FAILURE);
	if (close(fd) < 0)
		return (msg_perror("fd "));
	if (dup2(fd_tmp, STDIN_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (l_token->next->next->next)
		monitoring_line(l_token->next->next->next, envp, pipex);
	return (SUCCESS);
}
