/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:18:51 by agouet            #+#    #+#             */
/*   Updated: 2022/05/30 10:19:35 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_token(t_list	**l_token, char *line)
{	
	t_list	*l_new_token;
	char	**token;
	int		i;

	i = 0;
	token = lexer(line);
	while (token[i])
	{
		l_new_token = ft_lstnew(token[i]);
		if (!l_new_token)
			return (FAILURE);
		ft_lstadd_back(l_token, l_new_token);
		i++;
	}
	return (SUCCESS);
}

void	ft_lstclear2(t_list **l_token)
{
	t_list	*tmp;

	tmp = NULL;
	if (l_token)
	{
		while (*l_token)
		{
			tmp = (*l_token)->next;
			free((*l_token)->content);
			free(*l_token);
			*l_token = tmp;
		}
	}
}
