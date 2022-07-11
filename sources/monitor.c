/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:11:16 by agouet            #+#    #+#             */
/*   Updated: 2022/07/11 14:11:25 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	monitoring_line(t_list *l_token, char **envp, t_pipe pipex)
{
	char	**args_exec;

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
