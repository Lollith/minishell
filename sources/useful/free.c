/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lollith <lollith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:47:34 by agouet            #+#    #+#             */
/*   Updated: 2022/08/21 12:28:06 by lollith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_args_exec(char **args_exec, int ret)
{
	int	i;

	i = 0;
	while (args_exec[i])
	{
		free(args_exec[i]);
		i++;
	}
	free(args_exec);
	return (ret);
}

void	free_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	split_free_null(char **args_exec)
{
	if (args_exec != NULL)
		ft_split_free(args_exec);
}

//affichage liste chainee
	//while(pipex->l_start)
	//{
	//	printf("%s\n", (char*)pipex->l_start->content);
	//	pipex->l_start=pipex->l_start->next;
	//}
