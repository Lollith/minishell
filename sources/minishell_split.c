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

// #include "minishell.h"

// int	ft_strstr(char c, char *find)
// {
// 	int	i;

// 	i = 0;
// 	while (find[i])
// 	{
// 		if (c == find[i])
// 			return (TRUE);
// 		i++;
// 	}
// 	return (FALSE);
// }

// int	minishell_quote(char const *str, int i)
// {
// 	if (str[i] == '\"')
// 	{
// 		i++;
// 		while (str[i] != '\"')
// 		{
// 			if (str[i] == '\\')
// 				i++;
// 			i++;
// 		}
// 	}
// 	if (str[i] == '\'')
// 	{
// 		i++;
// 		if (str[i] != '\'')
// 		{
// 			if (str[i] == '\\')
// 				i++;
// 			i++;
// 		}
// 	}
// 	return (i);
// }

// int	minishell_count(char const *str, char *space)
// {
// 	int	i;
// 	int	j;
// 	int	res;

// 	i = 0;
// 	j = FALSE;
// 	res = 0;
// 	while (str[i])
// 	{
// 		i = minishell_quote(str, i);
// 		if (!j && !ft_strstr(str[i], space))
// 			j = TRUE;
// 		if (j && ft_strstr(str[i], space))
// 		{
// 			j = FALSE;
// 			res++;
// 		}
// 		i++;
// 	}
// 	return (res);
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

// char	**minishell_split(char const *str, char *space)
// {
// 	int		i;
// 	int		j;
// 	char	**res;

// 	res = malloc(sizeof(char *) * (minishell_count(str, space) + 1));
// 	if (!res)
// 		return (NULL);
// 	j = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		if (s[i])
// 			res[j] = ft_split_input(s, c, i);
// 		else
// 			break ;
// 		if (!res[j])
// 			return (ft_free_split(res));
// 		while (s[i] && s[i] != c)
// 			i++;
// 		j++;
// 	}
// 	res[j] = NULL;
// 	return (res);
// }
