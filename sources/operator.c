/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:15:29 by agouet            #+#    #+#             */
/*   Updated: 2022/06/07 15:47:49 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	monitoring_line(t_list *l_token, char **envp)
{
	char	**args_exec;

	args_exec = ft_is_arg(l_token);
	if (l_token->next)
	{
		if (ft_strncmp(l_token->next->content, "&&", 2) == 0)
			ft_eperluet(l_token, args_exec, envp);
		else if (ft_strncmp(l_token->next->content, "||", 2) == 0)
			ft_ou(l_token, args_exec, envp);
		else if (ft_strncmp(l_token->next->content, "|", 1) == 0)
			ft_pipex(l_token, args_exec, envp);
		else if (ft_strncmp(l_token->next->content, ">", 1) == 0
			|| ft_strncmp(l_token->next->content, ">|", 2) == 0)
			ft_redir_out(l_token, args_exec, envp);
	}
	else
	{
		if (ft_child(args_exec,envp, l_token) < 0)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_eperluet(t_list *l_token, char **new_token_exec, char **envp)
{
	if (ft_child(new_token_exec,envp, l_token) < 0)
		return (FAILURE);
	else
		monitoring_line(l_token->next->next, envp);
	return (SUCCESS);
}

int	ft_ou(t_list *l_token, char **new_token_exec, char **envp)
{
	if (ft_child(new_token_exec,envp, l_token) >= 0)
		return (SUCCESS);
	else
		monitoring_line(l_token->next->next, envp);
	return (SUCCESS);
}

int	ft_redir_out(t_list *l_token, char **new_token_exec, char **envp)
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
	if (ft_exec(envp, l_token->content, new_token_exec) == 0)
		return (FAILURE);
	if (close(fd) < 0)
		return (msg_perror("fd "));
	if (dup2(fd_tmp, STDOUT_FILENO) == -1)
		return (msg_perror("dup2 "));
	if (l_token->next->next->next)
		monitoring_line(l_token->next->next->next, envp);
	return (SUCCESS);
}
