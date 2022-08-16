/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:47:34 by agouet            #+#    #+#             */
/*   Updated: 2022/08/12 14:03:53 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_content(t_pipe *pipex)
{
	if (ft_strncmp(pipex->l_start->content, "<", 1) == 0)
	{
		free_null((void **)&pipex->l_start->content);
		free_null((void **)&pipex->l_start);
	}
}
