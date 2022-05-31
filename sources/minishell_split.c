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

// char	**ft_split_free(char **str)
// {
// 	int	i;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// 	return (NULL);
// }

// int	ft_split_count(char const *s, char c)
// {
// 	int	i;
// 	int	j;
// 	int	r;

// 	i = 0;
// 	j = 1;
// 	r = 0;
// 	while (s[i])
// 	{
// 		if (j && s[i] != c)
// 		{
// 			j = 0;
// 			r++;
// 		}
// 		if (!j && s[i] == c)
// 			j = 1;
// 		i++;
// 	}
// 	return (r);
// }

// int	ft_split_len(char const *s, char c, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == c)
// 			return (j);
// 		i++;
// 		j++;
// 	}
// 	return (j);
// }

// char	*ft_split_input(char const *s, char c, int i)
// {
// 	int		j;
// 	char	*res;

// 	res = malloc(sizeof(char) * (ft_split_len(s, c, i) + 1));
// 	if (!res)
// 		return (NULL);
// 	j = 0;
// 	while (s[i] && s[i] != c)
// 	{
// 		res[j] = s[i];
// 		i++;
// 		j++;
// 	}
// 	res[j] = '\0';
// 	return (res);
// }

// char	**minishell_split(char const *s, char c)
// {
// 	int		i;
// 	int		j;
// 	char	**res;

// 	res = malloc(sizeof(char *) * (ft_split_count(s, c) + 1));
// 	if (!res)
// 		return (NULL);
// 	j = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i])
// 			res[j] = ft_split_input(s, c, i);
// 		else
// 			break ;
// 		if (!res[j])
// 			return (ft_split_free(res));
// 		while (s[i] && s[i] != c)
// 			i++;
// 		j++;
// 	}
// 	res[j] = NULL;
// 	return (res);
// }
