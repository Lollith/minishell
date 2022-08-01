/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:08:20 by agouet            #+#    #+#             */
/*   Updated: 2022/07/13 15:04:01 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_first_strchr(const char *s, int c)
{
	if (s[0] == (char)c)
		return ((char *)s);
	return (NULL);
}

int	is_operator(t_list *l_token)
{
	char	c[4];
	int		i;

	i = 0;
	c[0] = '>';
	c[1] = '<';
	c[2] = '&';
	c[3] = '|';
	while (i < 4 && l_token)
	{
		if (ft_first_strchr(l_token->content, c[i]))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}
