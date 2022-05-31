/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:15:29 by agouet            #+#    #+#             */
/*   Updated: 2022/05/30 10:26:29 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	monitoring_line(t_list *tmp_token, char **envp)
{
	if (!ft_eperluet(tmp_token, envp))
		ft_ou(tmp_token, envp);
}

int	ft_eperluet(t_list *tmp_token, char **envp)
{
	char	**new_token_exec;

	new_token_exec = create_token_exec(tmp_token->content);
	if (tmp_token->next && ft_strncmp(tmp_token->next->content, "&&", 2) == 0)
	{
		if (ft_exec(envp, tmp_token->content, new_token_exec) == 0)
			return (FAILURE);
		else
			ft_eperluet(tmp_token->next->next, envp);
	}
	else if (!tmp_token->next)
		ft_exec(envp, tmp_token->content, new_token_exec);
	return (FAILURE);
}

// fct non operationnelle
// tester si 1er commande fail => doit lancer 2 eme commande
int	ft_ou(t_list *tmp_token, char **envp)
{
	char	**new_token_exec;

	new_token_exec = create_token_exec(tmp_token->content);
	if (tmp_token->next && ft_strncmp(tmp_token->next->content, "||", 2) == 0)
	{
		if (ft_exec(envp, tmp_token->content, new_token_exec) == 1)
			return (SUCCESS);
		else
			ft_eperluet(tmp_token->next->next, envp);
	}
	return (FAILURE);
}
