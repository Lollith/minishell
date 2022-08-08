/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:18:51 by agouet            #+#    #+#             */
/*   Updated: 2022/08/08 11:16:06 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_token(t_list **l_token, char *line)
{
	t_list	*l_new_token;
	char	**token;
	int		i;

	add_history(line);
	i = 0;
	token = lexer(line);
	if (!token)
		return (FAILURE);
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

	if (!l_token)
		return ;
	while (*l_token)
	{
		tmp = (*l_token)->next;
		free((*l_token)->content);
		free(*l_token);
		*l_token = tmp;
	}
}
