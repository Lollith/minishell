/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frrusso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:18 by frrusso           #+#    #+#             */
/*   Updated: 2022/05/25 12:07:31 by frrusso          ###   ########.fr       */
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
		{
			if (str[i] == '\\')
				i++;
			i++;
		}
	}
	if (str[i] == '\'')
	{
		i++;
		if (str[i] != '\'')
		{
			if (str[i] == '\\')
				i++;
			i++;
		}
	}
	return (i);
}

int	minishell_count(char const *str, char *space)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = ft_is_space(str[i], space);
	res = 1;
	while (str[i])
	{
		i = minishell_quote(str, i);
		if (!j && ft_is_space(str[i], space))
		{
			j = TRUE;
			res++;
		}
		if (j && !ft_is_space(str[i], space))
			j = FALSE;
		i++;
	}
	return (res);
}

int	minishell_len(char const *str, char *space, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (ft_is_space(str[i], space))
			return (j);
		i++;
		j++;
	}
	return (j);
}

char	*minishell_input(char const *str, char *space, int i)
{
	int		j;
	char	*res;

	res = malloc(sizeof(char) * (minishell_len(str, space, i) + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (str[i] && !ft_is_space(str[i], space))
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	**minishell_split(char const *str, char *space)
{
	int		i;
	int		j;
	char	**res;

	res = malloc(sizeof(char *) * minishell_count(str, space));
	if (!res)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i])
	{
		while (ft_is_space(str[i], space))
			i++;
		if (str[i])
			res[j] = minishell_input(str, space, i);
		else
			break ;
		if (!res[j])
			return (ft_split_free(res));
		while (str[i] && !ft_is_space(str[i], space))
			i++;
		j++;
	}
	res[j] = NULL;
	return (res);
}
