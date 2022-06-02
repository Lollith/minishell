/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:15:29 by agouet            #+#    #+#             */
/*   Updated: 2022/06/02 10:06:54 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_eperluet(t_list *l_token, char **envp)
{
	char	**new_token_exec;

	new_token_exec = create_token_exec(l_token->content);
	if (l_token->next && ft_strncmp(l_token->next->content, "&&", 2) == 0)
	{
		if (ft_exec(envp, l_token->content, new_token_exec) == 0)
			return (FAILURE);
		else
			ft_eperluet(l_token->next->next, envp);
	}
	else if (!l_token->next)
		ft_exec(envp, l_token->content, new_token_exec);
	return (FAILURE);
}

// fct non operationnelle
// tester si 1er commande fail => doit lancer 2 eme commande
int	ft_ou(t_list *l_token, char **envp)
{
	char	**new_token_exec;

	new_token_exec = create_token_exec(l_token->content);
	if (l_token->next && ft_strncmp(l_token->next->content, "||", 2) == 0)
	{
		if (ft_exec(envp, l_token->content, new_token_exec) == 1)
			return (SUCCESS);
		else
			ft_eperluet(l_token->next->next, envp);
	}
	return (FAILURE);
}

int	ft_redir_out(t_list *l_token, char **envp)
{
	int		fd;
	char	**new_token_exec;
	int		fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	new_token_exec = create_token_exec(l_token->content);
	if (l_token->next && ((ft_strncmp(l_token->next->content, ">", 1) == 0)
			|| ft_strncmp(l_token->next->content, ">|", 2) == 0))
	{
		fd = open(l_token->next->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
			return (msg_perror("open "));
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (msg_perror("dup2 "));
		if (ft_exec(envp, l_token->content, new_token_exec) == 0)
			return (FAILURE);
		if (close(fd) < 0)
			return (msg_perror("fd "));
		else
			ft_redir_out(l_token->next->next, envp);
		dup2(fd_tmp, STDOUT_FILENO);
	}
	else if (!l_token->next)
	{
		if (ft_exec(envp, l_token->content, new_token_exec) == 0)
			return (FAILURE);
	}
	return (FAILURE);
}
