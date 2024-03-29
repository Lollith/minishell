/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agouet <agouet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:07:18 by frrusso           #+#    #+#             */
/*   Updated: 2022/08/08 10:36:36 by agouet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_count(char const *str, char *space)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	j = ft_is_space(str[i], space);
	res = 2;
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
	int	res;

	res = 1;
	while (str[i])
	{
		i = minishell_len_quote(str, i, &res);
		if (ft_is_space(str[i], space))
			break ;
	}
	return (res);
}

char	*minishell_input(char const *str, char *space, int i)
{
	int		j;
	int		len;
	char	*res;

	len = minishell_len(str, space, i);
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	j = 0;
	while (--len)
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

int	minishell_post_input(char const *str, char *space, int i, char *res)
{
	int	input;

	input = ft_strlen(res);
	while (input)
	{
		input--;
		i++;
	}
	while (str[i] && !ft_is_space(str[i], space))
		i++;
	return (i);
}

char	**minishell_split(char const *str, char *space)
{
	int		i;
	int		j;
	char	**res;

	res = ft_calloc(sizeof(char *), minishell_count(str, space));
	if (!res)
		return (NULL);
	j = 0;
	i = 0;
	while (str && str[i])
	{
		while (ft_is_space(str[i], space))
			i++;
		if (str[i])
			res[j] = minishell_input(str, space, i);
		else
			break ;
		if (!res[j])
			return (ft_split_free(res));
		i = minishell_post_input(str, space, i, res[j]);
		j++;
	}
	return (res);
}
