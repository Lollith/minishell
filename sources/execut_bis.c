/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:25:11 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/19 08:19:44 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_free(char ***token, char ***envp, t_pipe *pipex, int ret)
{
	(void)pipex;
	ft_split_free(*token);
	ft_split_free(*envp);
	exit(ret);
}

void	ft_child_free2(char ***token, char ***envp, t_list *l_token, int ret)
{
	ft_lstclear2(&l_token);
	ft_split_free(*token);
	ft_split_free(*envp);
	exit(ret);
}
