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

int	ft_strstr(char c, char *to_find)
{
	int	n;

	n = 0;
	if (to_find[0] == '\0')
		return (0);
	while (to_find[n])
	{
		if (c == to_find[n])
			return (1);
		n++;
	}
	return (0);
}

int	ft_count_word(char *str, char *space)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (str[i])
	{
		if (ft_strstr(str[i], space) != 0)
			res++;
		while (str[i] && ft_strstr(str[i], space) != 0)
			i++;
		i++;
	}
	return (res);
}

int	ft_len_word(char *str, char *space, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (ft_strstr(str[i], space) != 0)
			return (j);
		i++;
		j++;
	}
	return (j);
}

char	*ft_input_word(char *str, char *space, int i)
{
	char	*word;
	int		k;

	k = 0;
	word = malloc(sizeof(char) * (ft_len_word(str, space, i) + 1));
	if (!word)
		return (NULL);
	while (str[i] && ft_strstr(str[i], space) == 0)
		word[k++] = str[i++];
	word[k] = '\0';
	return (word);
}

char	**minishell_split(char *str, char *space)
{
	int		i;
	int		c;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * ft_count_word(str, space) + 1);
	if (!res)
		return (NULL);
	c = 0;
	while (str[i])
	{
		while (str[i] && ft_strstr(str[i], space) == 1)
			i++;
		if (str[i])
			res[c] = ft_input_word(str, space, i);
		else
			res[c] = 0;
		while (str[i] && ft_strstr(str[i], space) == 0)
			i++;
		c++;
	}
	res[c] = NULL;
	return (res);
}
