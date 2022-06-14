/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:23:41 by frrusso           #+#    #+#             */
/*   Updated: 2022/06/07 15:23:44 by frrusso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c, char *space)
{
	int	i;

	i = 0;
	while (space[i])
	{
		if (c == space[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	minishell_quote(char const *str, int i)
{
	if (str[i] == '\"')
	{
		i++;
		while (str[i] != '\"')
			i++;
	}
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	return (i);
}

int	minishell_len_quote(char const *str, int i, int *j)
{
	if (str[i] == '\"')
	{
		i++;
		while (str[i] != '\"')
		{
			i++;
			*j += 1;
		}
		i++;
	}
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
		{
			i++;
			*j += 1;
		}
		i++;
	}
	return (i);
}
