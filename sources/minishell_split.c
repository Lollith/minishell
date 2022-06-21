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
	int	j;

	j = 1;
	while (str[i])
	{
		i = minishell_len_quote(str, i, &j);
		if (ft_is_space(str[i], space))
			break ;
	}
	return (j);
}

char	*minishell_input(char const *str, char *space, int i)
{
	int		j;
	int		k;
	int		len;
	char	*res;

	len = minishell_len(str, space, i);
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	j = 0;
	while (--len)
	{
		while (ft_is_space(str[i], "\"\'"))
			i++;
		if (str[i] == '$')
		{
			k = j;
			i = minishell_env_res(res, str, i, &j);
			len -= (j - k) - 1;
			continue ;
		}
		ft_chrcpy(str, res, &i, &j);
	}
	res[j] = '\0';
	return (res);
}

int	minishell_post_input(char const *str, char *space, int i, char *res)
{
	int	k;
	int	input;

	input = ft_strlen(res);
	while (input)
	{
		k = i;
		i = minishell_env_post_input(str, i, &input);
		if (!str[i])
			break ;
		if (k != i)
			continue ;
		if (!ft_is_space(str[i], "\"\'"))
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
		i = minishell_post_input(str, space, i, res[j]);
		j++;
	}
	res[j] = NULL;
	return (res);
}
