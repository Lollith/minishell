/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:37:19 by agouet            #+#    #+#             */
/*   Updated: 2022/07/11 16:37:22 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_eperluet(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	if (ft_child(args_exec, envp, l_token, pipex) == 0)
		return (FAILURE);
	else
		monitoring_line(l_token->next->next, envp, pipex);
	return (SUCCESS);
}

int	ft_ou(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	if (ft_child(args_exec, envp, l_token, pipex) == 0)
		return (FAILURE);
	else
		monitoring_line(l_token->next->next, envp, pipex);
	return (FAILURE);
}
