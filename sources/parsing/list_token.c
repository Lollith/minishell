/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:18:51 by agouet            #+#    #+#             */
/*   Updated: 2022/08/18 17:36:53 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_token(t_list **l_token, char *line, t_pipe *pipex)
{
	t_list	*l_new_token;
	char	**token;
	int		i;

	token = lexer(line, pipex);
	if (!token)
		return (FAILURE);
	add_history(line);
	i = 0;
	while (token[i])
	{
		l_new_token = ft_lstnew(token[i]);
		if (!l_new_token)
		{
			ft_split_free(token);
			return (FAILURE);
		}
		ft_lstadd_back(l_token, l_new_token);
		i++;
	}
	free(token);
	return (SUCCESS);
}

void	ft_l_delete(t_list *l_token)
{
	t_list	*tmp;

	tmp = l_token->next;
	if (l_token->next->next)
		l_token->next = l_token->next->next;
	else
		l_token->next = NULL;
	free(tmp->content);
	free(tmp);
}

void	ft_lstclear2(t_list **l_token)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!l_token)
		return ;
	tmp2 = *l_token;
	while (tmp2)
	{
		tmp = tmp2->next;
		free (tmp2->content);
		free (tmp2);
		tmp2 = tmp;
	}
	*l_token = NULL;
}

void	ft_lstclear3(t_list **l_token)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!l_token)
		return ;
	tmp2 = *l_token;
	while (tmp2)
	{
		tmp = tmp2->next;
		if (tmp2 && tmp2->content)
			free(tmp2->content);
		if (tmp2)
			free(tmp2);
		tmp2 = tmp;
	}
	*l_token = NULL;
}
