/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lollith <lollith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:47:34 by agouet            #+#    #+#             */
/*   Updated: 2022/08/21 18:35:15 by lollith          ###   ########.fr       */
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

//a utiliser avec free_null((void **))
void	free_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	**ft_split_free2(char **str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
	return (NULL);
}

void	split_free_null(char **args_exec)
{
	if (args_exec != NULL)
		ft_split_free2(args_exec);
}

void	ft_clean_redir(t_pipe *pipex)
{
	t_list	*tmp ;

	if (pipex->l_start != NULL && pipex->ctrl_redir == 1)
	{
		tmp = pipex->l_start->next;
		if (pipex->l_start->content != NULL)
			free(pipex->l_start->content);
		if (pipex->l_start != NULL)
			free(pipex->l_start);
		pipex->l_start = tmp;
		pipex->ctrl_redir2 = 1;
		pipex->ctrl_redir = 0;
	}
}

//affichage liste chainee
	//while(pipex->l_start)
	//{
	//	printf("%s\n", (char*)pipex->l_start->content);
	//	pipex->l_start=pipex->l_start->next;
	//}
