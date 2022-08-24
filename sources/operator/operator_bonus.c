/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:37:19 by agouet            #+#    #+#             */
/*   Updated: 2022/08/24 10:57:57 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_eperluet(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	int	status;

	ft_child(&args_exec, envp, l_token, pipex);
	wait(&status);
	if (WEXITSTATUS(status) != 0)
		return (FAILURE);
	else
		monitoring(l_token, l_token->next->next, envp, pipex);
	return (SUCCESS);
}

int	ft_ou(t_list *l_token, char **args_exec, char ***envp, t_pipe *pipex)
{
	int	status;

	ft_child(&args_exec, envp, l_token, pipex);
	wait(&status);
	if (WEXITSTATUS(status) != 0)
		monitoring(l_token, l_token->next->next, envp, pipex);
	else
		return (FAILURE);
	return (FAILURE);
}
