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

int	minishell_len_quote_bis(char const *str, int i, int *j, char c)
{
	*j += 2;
	i++;
	while (str[i] != c)
	{
		i++;
		*j += 1;
	}
	return (i + 1);
}

int	minishell_len_quote(char const *str, int i, int *j)
{
	if (str[i] == '\"')
		i = minishell_len_quote_bis(str, i, j, '\"');
	else if (str[i] == '\'')
		i = minishell_len_quote_bis(str, i, j, '\'');
	else
	{
		i++;
		*j += 1;
	}
	return (i);
}
