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

int	minishell_env_res(char *res, char const *str, int i, int *j)
{
	int		k;
	int		var;
	char	name[BUFFER_NAME];
	char	*value;

	i++;
	var = 0;
	while (ft_isalnum(str[i + var]))
		var++;
	ft_memcpy(name, str + i, var);
	name[var] = '\0';
	value = getenv(name);
	if (value)
	{
		k = 0;
		while (value[k])
		{
			res[*j] = value[k];
			k++;
			*j += 1;
		}
	}
	return (i + var);
}

int	minishell_env_var(char const *str, int i, int *j, int pp)
{
	int		var;
	char	name[BUFFER_NAME];
	char	*value;

	if (str[i] == '$')
	{
		i++;
		var = 0;
		while (ft_isalnum(str[i + var]))
			var++;
		ft_memcpy(name, str + i, var);
		name[var] = '\0';
		value = getenv(name);
		if (value)
			*j += ft_strlen(value);
		return (i + var);
	}
	return (i + pp);
}

int	minishell_len_quote(char const *str, int i, int *j)
{
	if (str[i] == '$' && str[i + 1] != '?')
		i = minishell_env_var(str, i, j, 0);
	else if (str[i] == '\"')
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
